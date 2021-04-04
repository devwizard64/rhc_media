/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#include <ultra64.h>
#include <gbi_ext.h>
#include <sm64.h>

#include "course.h"
#include "bgmap.h"

#define COURSE_TILE_MAX         2*(lenof(course_tile_flag)-1)

#define course_last()           \
    (course.type != 0 || course.index == COURSE_LEN-1)
#define course_text_k(i)        ((i) == -1 || (i) == 0x12 ? 4*8 : 4*16)

#define course_mode(s)          \
{                               \
    course.mode.state = s;      \
    course.mode.frame = 0;      \
}
#define course_mode_step()      {course.mode.state++;}
#define course_mode_next()      {course.mode.state++; course.mode.frame = 0;}
#define course_tile_step()      {course.tile.state++;}
#define course_tile_next()      {course.tile.state++; course.tile.frame = 0;}
#define course_text(t, m, s)    \
{                               \
    course.text[t].motion = m;  \
    course.text[t].frame  = 0;  \
    course.text[t].str    = s;  \
}
#define course_text_next(t)     \
{                               \
    course.text[t].motion++;    \
    course.text[t].frame = 0;   \
}

struct ct_frame_t
{
    s16 x;
    s16 y;
    u16 w;
    u16 h;
};

struct ct_motion_t
{
    s16 x;
    s16 y;
    s16 stride;
    u16 end;
    const struct ct_frame_t *frame;
};

struct course_meta_t
{
    const s16 *path;
    s16 xl;
    s16 xh;
    s16 yl;
    s16 yh;
    s16 zl;
    s16 zh;
    s16 offset;
    s16 stage;
};

struct course_mode_t
{
    u16 state;
    u16 frame;
};

struct course_text_t
{
    u16 motion;
    u16 frame;
    const char *str;
};

struct course_score_t
{
    u16 player;
    u16 opponent;
    u16 mode;
    u16 time;
};

struct course_t
{
    const struct course_meta_t *meta;
    f32  pos[3];
    s16  ry;
    u8   index;
    s8   type;
    struct object_t *object;
    struct course_mode_t mode;
    struct course_mode_t tile;
    struct course_text_t text[2];
    struct course_score_t score[COURSE_LEN];
    u16  coin[2];
    u16  total[2];
    char str[10];
    u8   win;
    bool latch;
};

extern const Gfx gfx_course_font_start[];
extern const Gfx *const gfx_course_tile[];
extern const u16 *const texture_course_font[];
extern const uintptr_t o_opponent[];

const Gfx gfx_print_start[] =
{
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetBlendColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

const Gfx gfx_print_end[] =
{
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

#define FLAG(a, b, c, d, e, f, g, h, i, j)              \
(                                                       \
    (a) <<  0 | (b) <<  2 | (c) <<  4 | (d) <<  6 |     \
    (e) <<  8 | (f) << 10 | (g) << 12 | (h) << 14 |     \
    (i) << 16 | (j) << 18                               \
)
#define __  0
#define _X  1
#define X_  2
#define XX  3
static const u32 course_tile_flag[] =
{
    FLAG(__, __, __, __, __, __, __, __, __, __),
    FLAG(_X, __, __, __, __, __, __, __, __, __),
    FLAG(_X, _X, __, __, __, __, __, __, __, __),
    FLAG(_X, _X, _X, __, __, __, __, __, __, __),
    FLAG(_X, _X, _X, _X, __, __, __, __, __, __),
    FLAG(_X, _X, _X, _X, _X, __, __, __, __, X_),
    FLAG(_X, _X, _X, _X, _X, _X, __, __, X_, X_),
    FLAG(_X, _X, _X, _X, _X, _X, _X, X_, X_, X_),
    FLAG(_X, _X, _X, _X, _X, _X, XX, XX, X_, X_),
    FLAG(_X, _X, _X, _X, _X, XX, XX, XX, XX, X_),
    FLAG(_X, _X, _X, _X, XX, XX, XX, XX, XX, XX),
    FLAG(_X, _X, _X, XX, XX, XX, XX, XX, XX, XX),
    FLAG(_X, _X, XX, XX, XX, XX, XX, XX, XX, XX),
    FLAG(_X, XX, XX, XX, XX, XX, XX, XX, XX, XX),
    FLAG(XX, XX, XX, XX, XX, XX, XX, XX, XX, XX),
};
#undef FLAG
#undef __
#undef _X
#undef X_
#undef XX

#define FRAME(x, y, w, h)   {4*(x), 4*(y), (int)(0x100*(w)), (int)(0x100*(h))}
static const struct ct_frame_t ct_frame_0[] =
{
    FRAME(40* 10, 0, 1.0F, 1.0F),
    FRAME(40*  9, 0, 1.0F, 1.0F),
    FRAME(40*  8, 0, 1.0F, 1.0F),
    FRAME(40*  7, 0, 1.0F, 1.0F),
    FRAME(40*  6, 0, 1.0F, 1.0F),
    FRAME(40*  5, 0, 1.0F, 1.0F),
    FRAME(40*  4, 0, 1.0F, 1.0F),
    FRAME(40*  3, 0, 1.0F, 1.0F),
    FRAME(40*  2, 0, 0.9F, 1.2F),
    FRAME(40*  1, 0, 0.8F, 1.4F),
    FRAME(40*  0, 0, 0.7F, 1.6F),
    FRAME(40*  0, 0, 0.6F, 1.8F),
    FRAME(40*  0, 0, 0.5F, 2.0F),
    FRAME(40*  0, 0, 0.5F, 2.0F),
    FRAME(40*  0, 0, 0.6F, 1.8F),
    FRAME(40*  0, 0, 0.8F, 1.4F),
    FRAME(40*  0, 0, 0.9F, 1.2F),
    FRAME(40*  0, 0, 1.0F, 1.0F),
};
static const struct ct_frame_t ct_frame_1[] =
{
    FRAME(32*  0, 0, 1.0F, 1.0F),
    FRAME(32* -1, 0, 1.0F, 1.0F),
    FRAME(32* -2, 0, 1.0F, 1.0F),
    FRAME(32* -3, 0, 1.0F, 1.0F),
    FRAME(32* -4, 0, 1.0F, 1.0F),
    FRAME(32* -5, 0, 1.0F, 1.0F),
    FRAME(32* -6, 0, 1.0F, 1.0F),
    FRAME(32* -7, 0, 1.0F, 1.0F),
    FRAME(32* -8, 0, 1.0F, 1.0F),
    FRAME(32* -9, 0, 1.0F, 1.0F),
    FRAME(32*-10, 0, 1.0F, 1.0F),
    FRAME(32*-11, 0, 1.0F, 1.0F),
    FRAME(32*-12, 0, 1.0F, 1.0F),
};
static const struct ct_frame_t ct_frame_2[] =
{
    FRAME(0, 180, 1.0F, 1.0F),
    FRAME(0, 140, 1.0F, 1.0F),
    FRAME(0, 100, 1.0F, 1.0F),
    FRAME(0,  60, 1.0F, 1.0F),
    FRAME(0,  20, 1.0F, 1.0F),
    FRAME(0, -20, 1.0F, 1.0F),
    FRAME(0, -40, 1.0F, 1.0F),
    FRAME(0, -50, 1.0F, 1.0F),
    FRAME(0, -55, 1.0F, 1.0F),
    FRAME(0, -60, 1.0F, 1.0F),
    FRAME(0, -55, 1.0F, 1.0F),
    FRAME(0, -50, 1.0F, 1.0F),
    FRAME(0, -40, 1.0F, 1.0F),
    FRAME(0, -20, 1.0F, 1.0F),
    FRAME(0,   0, 1.0F, 1.0F),
    FRAME(0,   0, 1.0F, 0.8F),
    FRAME(0,   0, 1.0F, 0.6F),
    FRAME(0,   0, 1.0F, 0.4F),
    FRAME(0,   0, 1.0F, 0.2F),
    FRAME(0,   0, 1.0F, 0.4F),
    FRAME(0,   0, 1.0F, 0.6F),
    FRAME(0,   0, 1.0F, 0.8F),
    FRAME(0,   0, 1.0F, 1.0F),
};
static const struct ct_frame_t ct_frame_3[] =
{
    FRAME(0, 16* 0, 1.0F, 1.0F),
    FRAME(0, 16* 1, 1.0F, 1.0F),
    FRAME(0, 16* 2, 1.0F, 1.0F),
    FRAME(0, 16* 3, 1.0F, 1.0F),
    FRAME(0, 16* 4, 1.0F, 1.0F),
    FRAME(0, 16* 5, 1.0F, 1.0F),
    FRAME(0, 16* 6, 1.0F, 1.0F),
    FRAME(0, 16* 7, 1.0F, 1.0F),
    FRAME(0, 16* 8, 1.0F, 1.0F),
    FRAME(0, 16* 9, 1.0F, 1.0F),
    FRAME(0, 16*10, 1.0F, 1.0F),
    FRAME(0, 16*11, 1.0F, 1.0F),
};
static const struct ct_frame_t ct_frame_4[] =
{
    FRAME(8* 24, 0, 1.0F, 1.0F),
    FRAME(8* 20, 0, 1.0F, 1.0F),
    FRAME(8* 16, 0, 1.0F, 1.0F),
    FRAME(8* 12, 0, 1.0F, 1.0F),
    FRAME(8*  8, 0, 1.0F, 1.0F),
    FRAME(8*  4, 0, 1.0F, 1.0F),
    FRAME(8*  2, 0, 1.0F, 1.0F),
    FRAME(8*  1, 0, 1.0F, 1.0F),
    FRAME(8*  0, 0, 1.0F, 1.0F),
};
static const struct ct_frame_t ct_frame_5[] =
{
    FRAME(8*  0, 0, 1.0F, 1.0F),
    FRAME(8* -1, 0, 1.0F, 1.0F),
    FRAME(8* -2, 0, 1.0F, 1.0F),
    FRAME(8* -4, 0, 1.0F, 1.0F),
    FRAME(8* -8, 0, 1.0F, 1.0F),
    FRAME(8*-12, 0, 1.0F, 1.0F),
    FRAME(8*-16, 0, 1.0F, 1.0F),
    FRAME(8*-20, 0, 1.0F, 1.0F),
    FRAME(8*-24, 0, 1.0F, 1.0F),
    FRAME(8*-28, 0, 1.0F, 1.0F),
};
#undef FRAME

#define MOTION(x, y, stride, name)      \
    {4*(x), 4*(y), stride, lenof(ct_frame_##name)-1, ct_frame_##name}
static const struct ct_motion_t ct_motion[] =
{
    MOTION(160,  80, -1, 0),
    MOTION(160,  80, -1, 1),
    MOTION(160,  80, -1, 2),
    MOTION(160,  80, -1, 3),
    MOTION(160, 110,  0, 4),
    MOTION(160, 110,  0, 5),
};
#undef MOTION

extern const s16 path_stage_course1_1[];
extern const s16 path_stage_course2_1[];
/* extern const s16 path_stage_course3_1[]; */
#define path_stage_course3_1 NULL

static const struct course_meta_t course_meta_table[] =
{
    {path_stage_course1_1,  4192,  8192, -2048,  8192, -8192,  8192,  64, 2},
    {path_stage_course2_1,  3840,  8192,  2048,  8192, -8192,  8192,  64, 4},
    {path_stage_course3_1,  3240,  3368, -8192,  8192, -4667, -4539, 256, 4},
};

static struct course_t course;
u16 course_coin;

s32 course_menu(unused s16 arg, unused s32 state)
{
    uint i;
    menu_scroll_v(&course.type, 0, COURSE_LEN);
    print(160 - 6*10, 89 - 18*0, "grand prix");
    for (i = 1; i <= COURSE_LEN; i++)
    {
        print_int(160 - 6*10, 89 - 18*i, "course %d", i);
    }
    print(160 - 6*13, 89 - 18*course.type, "-");
    if (app_pad_menu->down & (A_BUTTON | START_BUTTON))
    {
        audio_sfx_play(SFX_SYS_START, audio_sfx_org);
        return course.type == 0 ? 1 : course.type;
    }
    if (main_debug_mem)
    {
        print(160 - 6*20, 216, "Mario no Gourmetrace");
        if (app_pad_menu->down & L_TRIG)
        {
            audio_sfx_play(SFX_SYS_START, audio_sfx_org);
            return 4;
        }
    }
    return 0;
}

s32 course_end_init(unused s16 arg, unused s32 state)
{
    uint i;
    course.coin[0]  = 0;
    course.coin[1]  = 0;
    course.total[0] = 0;
    course.total[1] = 0;
    for (i = 0; i < COURSE_LEN; i++)
    {
        course.coin[0] += course.score[i].player;
        course.coin[1] += course.score[i].opponent;
        course.total[course.score[i].mode] += 30;
    }
    course.total[0] += course.coin[0];
    course.total[1] += course.coin[1];
    course.win = course.total[1] > course.total[0];
    course.mode.frame = 0;
    return 1;
}

#define END_XL          60
#define END_XH          180
#define END_TITLE_Y     (192-18*0)
#define END_COIN_Y      170
#define END_WIN_Y       130
#define END_TOTAL_Y     100

s32 course_end_update(unused s16 arg, unused s32 state)
{
    uint frame = course.mode.frame;
    uint cp;
    uint co;
    uint tp;
    uint to;
    uint i;
    if (course.mode.frame < 0xFFFF)
    {
        course.mode.frame++;
    }
    if (frame < 30*4)
    {
        cp = course.coin[0] * frame / (30*4);
        co = course.coin[1] * frame / (30*4);
        tp = to = 111 * (frame%10);
    }
    else
    {
        cp = course.coin[0];
        co = course.coin[1];
        tp = course.total[0];
        to = course.total[1];
    }
    print(160 - 6*5, END_TITLE_Y, "score");
    print(END_XL + 16*0, END_COIN_Y, "+");
    print(END_XL + 16*1, END_COIN_Y, "*");
    print_int(END_XL + 16*2, END_COIN_Y, "%03d", cp);
    print(END_XH + 16*0, END_COIN_Y, "+");
    print(END_XH + 16*1, END_COIN_Y, "*");
    print_int(END_XH + 16*2, END_COIN_Y, "%03d", co);
    print(END_XL, END_TOTAL_Y, "total");
    print_int(END_XL + 12*2, END_TOTAL_Y-18, "%03d", tp);
    print(END_XH, END_TOTAL_Y, "total");
    print_int(END_XH + 12*2, END_TOTAL_Y-18, "%03d", to);
    for (i = 0; i < COURSE_LEN; i++)
    {
        if (frame >= (30*4/(1+COURSE_LEN)) * (1+i))
        {
            int x = END_XL + 12 + 24*i;
            if (course.score[i].mode != 0)
            {
                x += END_XH-END_XL;
            }
            print(x, END_WIN_Y, "W");
        }
    }
    if (frame == 30*6)
    {
        return 1 + course.win;
    }
    return 0;
}

s32 course_message(s16 arg, unused s32 state)
{
    switch (arg)
    {
        case 0:
            if (course.win == 0)
            {
                print(160 - 6*3, 180, "win");
            }
            else
            {
                print(160 - 6*4, 180, "lose");
            }
            break;
        case 1:
            print(160 - 6*18, 200, "thanks for playing");
            print(160 - 6*14,  20, "written by mks");
            break;
    }
    if (app_pad_menu->down & (A_BUTTON | B_BUTTON | START_BUTTON))
    {
        return 1;
    }
    return 0;
}

uint course_lock(void)
{
    return course.mode.state ^ 2;
}

uint course_lose(void)
{
    return course.win ^ 0;
}

struct object_t *course_object(void)
{
    return course.object;
}

void course_out(void)
{
    world_wipe(0x01, 16, 0x00, 0x00, 0x00);
    course_mode(4);
}

void course_latch(void)
{
    course.latch = false;
}

static void course_start(struct player_t *player, uint frame)
{
    course.mode.state = 1;
    course.mode.frame = frame;
    course.text[0].str = NULL;
    course.text[1].str = NULL;
    player_state_set(player, PLAYER_STATE_WAITMSG, 0);
    world_wipe(0x00, 16, 0xFF, 0xFF, 0xFF);
}

s32 course_init(s16 arg, unused s32 state)
{
    struct player_t *player = &game_player_table[0];
    course.meta   = &course_meta_table[arg];
    course.pos[0] = player->pos[0];
    course.pos[1] = player->pos[1];
    course.pos[2] = player->pos[2];
    course.ry     = player->rot[1];
    course.index  = arg;
    course.object = object_init(player->object, 0, G_O_KOOPA, o_opponent);
    course.object->o_pos_x = course.pos[0] + course.meta->offset*cos(course.ry);
    course.object->o_pos_y = course.pos[1];
    course.object->o_pos_z = course.pos[2] - course.meta->offset*sin(course.ry);
    course.object->o_rot_y = course.ry;
    course.object->o_opponent_path = mem_segment(course.meta->path);
    course.tile.state = 1;
    course.tile.frame = COURSE_TILE_MAX;
    course.win = 0;
    course_coin = 0;
    course_start(player, 0);
    game_timer_show();
    return 1;
}

static void course_destroy(void)
{
    course.mode.state = 0;
    course.tile.state = 0;
}

static void course_startmove(void)
{
    struct player_t *player = &game_player_table[0];
    player_state_set(player, PLAYER_STATE_IDLE, 0);
    course.object->o_state = 1;
    game_timer_start();
    audio_sfx_play(SFX_GS1_GUNSHOT, audio_sfx_org);
}

static void course_endmove(uint mode)
{
    struct player_t *player = &game_player_table[0];
    uint time;
    uint m;
    uint s;
    uint f;
    course_mode_next();
    course.win = mode;
    course.latch = true;
    course.object->o_state++;
    course.score[course.index].player   = player->coin;
    course.score[course.index].opponent = course.object->o_opponent_coin;
    course.score[course.index].mode     = mode;
    course.score[course.index].time     = time = game_timer_stop();
    m = (time/30) / 60;
    s = (time/30) % 60;
    f = (time%30) * 100/30;
    sprintf(course.str, "%02d:%02d:%02d", m, s, f);
    player_state_set(player, PLAYER_STATE_SPAWNAIR, 0);
    audio_sfx_play(SFX_GS1_CORRECT | 0xFF00, audio_sfx_org);
}

static uint course_checkpoint(f32 *pos)
{
    int xl = course.meta->xl;
    int xh = course.meta->xh;
    int yl = course.meta->yl;
    int yh = course.meta->yh;
    int zl = course.meta->zl;
    int zh = course.meta->zh;
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];
    return x >= xl && x <= xh && y >= yl && y <= yh && z >= zl && z <= zh;
}

s32 course_update(s16 arg, s32 state)
{
    struct player_t *player;
    uint frame;
    state = game_main(arg, state);
    player = &game_player_table[0];
    frame = course.mode.frame;
    if (course.mode.frame < 0xFFFF)
    {
        course.mode.frame++;
    }
    switch (course.mode.state)
    {
        case 1:
            switch (frame)
            {
                case 30*1+ 0:
                    course_tile_step();
                    break;
                case 30*1+ 6:
                    course_text(0, 0, "ready!");
                    break;
                case 30*2+27:
                    course_text_next(0);
                    break;
                case 30*3+ 9:
                    course_text(1, 0, "go!");
                    break;
                case 30*3+20:
                    course_startmove();
                    course_mode_step();
                    break;
            }
            break;
        case 2:
            switch (frame)
            {
                case 30*4+10:
                    course_text_next(1);
                    break;
            }
            if (course_checkpoint(player->pos))
            {
                course_endmove(0);
            }
            else if (course_checkpoint(&course.object->o_pos_x))
            {
                course_endmove(1);
            }
            break;
        case 3:
            if (player->state == PLAYER_STATE_IDLE)
            {
                uint motion;
                if (course.win == 0)
                {
                    player->object->go.rot[1] = camera_ptr->yaw;
                    motion = PLAYER_MOTION_WINDEMO;
                }
                else
                {
                    motion = PLAYER_MOTION_MESSAGE;
                }
                player_motion_set(player, motion);
                player_state_set(player, PLAYER_STATE_NULL, 0);
            }
            if (course.win == 0)
            {
                if (player->object->go.motion.frame >= 38)
                {
                    player->gfx->gloves = 2;
                }
            }
            else
            {
                if (course.latch)
                {
                    course.mode.frame = 0;
                    break;
                }
            }
            switch (frame)
            {
                case 30*0+ 0:
                    if (course_last())
                    {
                        course_text(0, 0, "goal!");
                    }
                    else
                    {
                        course_text(0, 2, "checkpoint");
                    }
                    break;
                case 30*1+ 0:
                    course_text(1, 4, course.str);
                    break;
                case 30*4+ 0:
                    if (!course_last())
                    {
                        course_text_next(0);
                    }
                    break;
                case 30*4+20:
                    course_text_next(1);
                    break;
                case 30*4+25:
                    if (course_last())
                    {
                        course_text_next(0);
                    }
                    break;
                case 30*5+20:
                    course_tile_step();
                    break;
                case 30*6+20:
                    game_state_end_wipe(
                        course.type == 0 ? course.meta->stage : -1, true
                    );
                    break;
            }
            break;
        case 4:
            if (frame >= 16)
            {
                player->pos[0] = course.pos[0];
                player->pos[1] = course.pos[1];
                player->pos[2] = course.pos[2];
                player->rot[1] = course.ry;
                player->vel_f  = 0;
                course_start(player, 30*2+27);
            }
            break;
    }
    if (app_frame & 1)
    {
        if (course_coin < course.object->o_opponent_coin)
        {
            course_coin++;
            audio_sfx_play(0x30208081, audio_sfx_org);
        }
    }
    if (state != 0)
    {
        course_destroy();
    }
    if (main_debug_mem)
    {
        print_int(20, 180 - 18*0, "x %d", player->pos[0]);
        print_int(20, 180 - 18*1, "y %d", player->pos[1]);
        print_int(20, 180 - 18*2, "z %d", player->pos[2]);
    }
    return state;
}

void course_draw_tile(void)
{
    uint flag = course_tile_flag[course.tile.frame/2];
    switch (course.tile.state)
    {
        case 0:
            return;
        case 2:
            if (--course.tile.frame <= 0)
            {
                course_tile_step();
            }
            break;
        case 4:
            if (++course.tile.frame >= COURSE_TILE_MAX)
            {
                course_tile_step();
            }
        break;
    }
    if (flag != 0)
    {
        const Gfx *const *gfx_tile;
        Mtx *m;
        uint  i;
        gfx_tile = mem_segment(gfx_course_tile);
        gSPClearGeometryMode(video_gfx++, G_LIGHTING);
        m = mem_alloc_gfx(sizeof(*m));
        guOrtho(m, 0, 160, 120, 0, -2, 2, 1);
        gSPMatrix(video_gfx++, m, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        m = mem_alloc_gfx(sizeof(*m));
        guRotate(m, 360 * (-1.0F/16.0F), 0, 0, 1);
        gSPMatrix(video_gfx++, m, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
        for (i = 0; i < 10; i++)
        {
            uint x = flag >> (2*i);
            if (x & 3)
            {
                m = mem_alloc_gfx(sizeof(*m));
                guTranslate(m, COURSE_TILE_S*((signed)i-3), 0, 0);
                gSPMatrix(
                    video_gfx++, m, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH
                );
                if (x & 1)
                {
                    gSPDisplayList(video_gfx++, gfx_tile[0 + (i&1)]);
                }
                if (x & 2)
                {
                    gSPDisplayList(video_gfx++, gfx_tile[2 + (i&1)]);
                }
                gSPPopMatrix(video_gfx++, G_MTX_MODELVIEW);
            }
        }
        gSPPopMatrix(video_gfx++, G_MTX_MODELVIEW);
        gSPSetGeometryMode(video_gfx++, G_LIGHTING);
    }
}

static int course_text_i(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - ('0'-0x00);
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - ('A'-0x0A);
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - ('a'-0x0A);
    }
    else switch (c)
    {
        case '!': return 0x24; break;
        case ':': return 0x25; break;
    }
    return -1;
}

static uint course_text_w(const char *str)
{
    uint w = 0;
    while (*str != 0x00)
    {
        int i = course_text_i(*str);
        w += course_text_k(i);
        str++;
    }
    return w;
}

static void course_text_c(int x, int y, uint w, uint h, const u16 *timg)
{
    int xh = x + w;
    int yh = y + h;
    if (x < 4*320 && y < 4*232 && xh > 0 && yh > 8)
    {
        uint dsdx = 0x0400*4*COURSE_FONT_W / w;
        uint dtdy = 0x0400*4*COURSE_FONT_H / h;
        int  s;
        int  t;
        if (x < 0)
        {
            s = ((unsigned)-x * dsdx) >> 5;
            x = 0;
        }
        else
        {
            s = 0;
        }
        if (y < 0)
        {
            t = ((unsigned)-y * dtdy) >> 5;
            y = 0;
        }
        else
        {
            t = 0;
        }
        gDPSetTextureImage(video_gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, timg);
        gDPLoadTextureBlock2(
            video_gfx++, G_IM_SIZ_16b, COURSE_FONT_W, COURSE_FONT_H
        );
        gSPTextureRectangle(
            video_gfx++, x, y, xh, yh, G_TX_RENDERTILE, s, t, dsdx, dtdy
        );
        gDPPipeSync(video_gfx++);
    }
}

static void course_draw_text(void)
{
    if (course.mode.state != 0)
    {
        const u16 *const *texture_font = mem_segment(texture_course_font);
        uint i;
        gSPDisplayList(video_gfx++, gfx_course_font_start);
        for (i = 0; i < lenof(course.text); i++)
        {
            struct course_text_t *text = &course.text[i];
            const char *str = text->str;
            if (str != NULL)
            {
                const struct ct_motion_t *motion = &ct_motion[text->motion];
                int f = text->frame;
                int px = motion->x - course_text_w(str)/2;
                int py = motion->y;
                int cx = 0;
                int cy = -2*COURSE_FONT_H;
                while (*str != 0x00)
                {
                    int  i  = course_text_i(*str);
                    uint cw = course_text_k(i);
                    if (i >= 0)
                    {
                        const u16 *timg = texture_font[i];
                        const struct ct_frame_t *frame;
                        int x;
                        int y;
                        int w;
                        int h;
                        i = f;
                        f += motion->stride;
                        if (i < 0)
                        {
                            i = 0;
                        }
                        if (i > motion->end)
                        {
                            i = motion->end;
                        }
                        frame = &motion->frame[i];
                        x = px + (cx+frame->x    ) * frame->w/0x100;
                        y = py + (cy+frame->y    ) * frame->h/0x100;
                        w =      (4*COURSE_FONT_W) * frame->w/0x100;
                        h =      (4*COURSE_FONT_H) * frame->h/0x100;
                        course_text_c(x, y, w, h, timg);
                    }
                    cx += cw;
                    str++;
                }
                if (text->frame < 0xFFFF)
                {
                    text->frame++;
                }
            }
        }
        gSPDisplayList(video_gfx++, gfx_course_end);
    }
}

void course_draw(void)
{
    course_draw_text();
    course_draw_tile();
}
