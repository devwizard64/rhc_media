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

#define BGMAP_TW                32
#define BGMAP_TH                64
#define BGMAP_H                 BGMAP_TH
#define BGMAP_TN                (320/BGMAP_TH + 1)
#define BGMAP_MH                (4*BGMAP_H)

#define BGMAP_C1_W              224
#define BGMAP_C1_H              336
#define BGMAP_C1_MH             (4*320)
#define BGMAP_C1_Y              (4*(240-BGMAP_C1_W)/2)

#define BGMAP_C2_W              192
#define BGMAP_C2_H              256
#define BGMAP_C2_MH             (4*BGMAP_C2_H)
#define BGMAP_C2_Y              (4*(240-BGMAP_C2_W)/2)

#define bgmap_out(y, n)         \
    ((y) > (0x1000*(n) - 0x1800) && (y) < (0x1000*(n) - 0x1400))

struct bgmap_link_t
{
    const s16 *path;
    s16 xl;
    s16 xh;
    s16 org;
    s16 t;
};

struct bgmap_t
{
    const struct bgmap_link_t *link;
    void (*callback)(uint);
    const void *const *szp_table;
    u8  szp_max;
    u8  w;
    s16 y;
};

#define BGMAP_S(b)
#define BGMAP_N(b, i)   extern const u8 szp_bgmap_##b##_##i##_start[];
#define BGMAP_E(b)      extern const u8 szp_bgmap_##b##_end[];
#include "bgmap/course1.h"
#include "bgmap/course2.h"
#undef BGMAP_S
#undef BGMAP_N
#undef BGMAP_E

#define BGMAP_S(b)      static const void *const szp_bgmap_##b##_table[] = {
#define BGMAP_N(b, i)   szp_bgmap_##b##_##i##_start,
#define BGMAP_E(b)      szp_bgmap_##b##_end, };
#include "bgmap/course1.h"
#include "bgmap/course2.h"
#undef BGMAP_S
#undef BGMAP_N
#undef BGMAP_E

extern const u16 texture_stage_course1_bg[];

extern const u16 texture_stage_course1_wa_0[];
extern const u16 texture_stage_course1_wa_1[];
extern const u16 texture_stage_course1_wa_2[];
extern const u16 texture_stage_course1_wa_3[];
extern const u16 texture_stage_course1_wa_4[];
extern const u16 texture_stage_course1_wa_5[];
extern const u16 texture_stage_course1_wb_0[];
extern const u16 texture_stage_course1_wb_1[];
extern const u16 texture_stage_course1_wb_2[];
extern const u16 texture_stage_course1_wb_3[];
extern const u16 texture_stage_course1_wb_4[];
extern const u16 texture_stage_course1_wb_5[];
static const u16 *const texture_stage_course1_w[][2] =
{
    {texture_stage_course1_wa_0, texture_stage_course1_wb_0},
    {texture_stage_course1_wa_1, texture_stage_course1_wb_1},
    {texture_stage_course1_wa_2, texture_stage_course1_wb_2},
    {texture_stage_course1_wa_3, texture_stage_course1_wb_3},
    {texture_stage_course1_wa_4, texture_stage_course1_wb_4},
    {texture_stage_course1_wa_5, texture_stage_course1_wb_5},
};

extern const u16 texture_stage_course2_bg[];
extern const Gfx gfx_stage_course2[];

extern const s16 path_stage_course1_2[];
extern const s16 path_stage_course2_2[];
extern const s16 path_stage_course2_3[];

static void bgmap_course1(uint);
static void bgmap_course2(uint);

#define LINK(i, n, xl, xh, path)    {path, xl, xh, BGMAP_O(i, n), BGMAP_T(i, n)}

static const struct bgmap_link_t bgmap_link_course1[] =
{
    LINK(1, 1,              -32768, BGMAP_O(1, 1)+C1_L2, NULL),
    LINK(1, 2, BGMAP_O(1, 2)+C1_L2,               32767, path_stage_course1_2),
};

static const struct bgmap_link_t bgmap_link_course2[] =
{
    LINK(2, 1,              -32768, BGMAP_O(2, 1)+C2_L2, NULL),
    LINK(2, 2, BGMAP_O(2, 2)+C2_L2, BGMAP_O(2, 2)+C2_L3, path_stage_course2_2),
    LINK(2, 3, BGMAP_O(2, 3)+C2_L3,               32767, path_stage_course2_3),
};

static const struct bgmap_t bgmap_table[] =
{
    {
        bgmap_link_course1,
        bgmap_course1,
        szp_bgmap_course1_table, lenof(szp_bgmap_course1_table)-1,
        BGMAP_C1_W, BGMAP_C1_Y,
    },
    {
        bgmap_link_course2,
        bgmap_course2,
        szp_bgmap_course2_table, lenof(szp_bgmap_course2_table)-1,
        BGMAP_C2_W, BGMAP_C2_Y,
    },
};

extern u8 bgmap_szp[];

#define static

static const struct bgmap_t *bgmap;
static u16  *bgmap_img[BGMAP_TN];
static u8    bgmap_pos[BGMAP_TN];
static f32   bgmap_offset;

#undef static

static void bgmap_draw(const u16 *timg, uint w, uint h, int x, int y)
{
    uint i;
    uint n;
    gDPSetTextureTile2(
        video_gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, BGMAP_TW, 0,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );
    w /= BGMAP_TW;
    h /= BGMAP_TH;
    for (i = 0; i < h; i++)
    {
        int xl;
        int xh;
        xl = x;
        x += 4*BGMAP_TH;
        xh = x;
        if (xl < 4*320 && xh > 4*0)
        {
            int  wy;
            uint ult;
            uint lrt;
            uint t;
            wy = y;
            ult = BGMAP_TH*i;
            lrt = BGMAP_TH+ult - 1;
            t = 32*ult;
            if (xl < 0)
            {
                t -= 8*xl;
                xl = 0;
            }
            if (xh > 4*320)
            {
                xh = 4*320;
            }
            for (n = 0; n < w; n++)
            {
                int yl;
                int yh;
                yl = wy;
                wy += 4*BGMAP_TW;
                yh = wy;
                if (yl < 4*232 && yh > 4*8)
                {
                    uint uls;
                    uint lrs;
                    uint s;
                    uls = BGMAP_TW*n;
                    lrs = BGMAP_TW+uls - 1;
                    s = 32*uls;
                    yl -= 4*8;
                    if (yl < 0)
                    {
                        s -= 8*yl;
                        yl = 0;
                    }
                    yl += 4*8;
                    if (yh > 4*232)
                    {
                        yh = 4*232;
                    }
                    gDPLoadSync(video_gfx++);
                    gDPLoadTextureTile2(video_gfx++, uls, ult, lrs, lrt);
                    gSPTextureRectangleFlip(
                        video_gfx++, xl, yl, xh, yh, G_TX_RENDERTILE, s, t,
                        0x0400, 0x0400
                    );
                    gDPPipeSync(video_gfx++);
                }
            }
        }
    }
}

static void water_draw(const u16 *timg, uint h, int x, int y)
{
    uint i;
    gDPSetTextureTile2(
        video_gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    );
    for (i = 0; i < h; i++)
    {
        int xl;
        int xh;
        xl = x;
        x += 4*24;
        xh = x;
        if (xl < 4*320 && xh > 4*0)
        {
            uint ult;
            uint t;
            ult = 24*i;
            t = 32*ult;
            if (xl < 0)
            {
                t -= 8*xl;
                xl = 0;
            }
            if (xh > 4*320)
            {
                xh = 4*320;
            }
            gDPLoadSync(video_gfx++);
            gDPLoadTextureTile2(video_gfx++, 0, ult, 40-1, ult+24-1);
            gSPTextureRectangleFlip(
                video_gfx++, xl, y, xh, y+4*40, G_TX_RENDERTILE, 0, t,
                0x0400, 0x0400
            );
            gDPPipeSync(video_gfx++);
        }
    }
}

static void bgmap_course1(uint i)
{
    int x = -(i/2 % BGMAP_C1_MH);
    const u16 *const *w;
    bgmap_draw(texture_stage_course1_bg, BGMAP_C1_W, BGMAP_C1_H, x, BGMAP_C1_Y);
    x += BGMAP_C1_MH;
    bgmap_draw(texture_stage_course1_bg, BGMAP_C1_W, BGMAP_C1_H, x, BGMAP_C1_Y);
    w = texture_stage_course1_w[app_frame/8 % lenof(texture_stage_course1_w)];
    water_draw(w[0], 2, 4*1584 - i, 4*(8+ 88));
    water_draw(w[1], 3, 4*2256 - i, 4*(8+112));
}

static void bgmap_course2_x(int x, int y)
{
    bgmap_draw(texture_stage_course2_bg, BGMAP_C2_H, BGMAP_C2_H, x, y);
    y += BGMAP_C2_MH;
    bgmap_draw(texture_stage_course2_bg, BGMAP_C2_H, BGMAP_C2_H, x, y);
}

static void bgmap_course2(uint i)
{
    int y;
    int x;
    gSPDisplayList(video_gfx++, gfx_stage_course2);
    y = BGMAP_C2_Y - (8*app_frame % BGMAP_C2_MH);
    x = -(i % BGMAP_C2_MH);
    bgmap_course2_x(x, y);
    x += BGMAP_C2_MH;
    bgmap_course2_x(x, y);
    x += BGMAP_C2_MH;
    bgmap_course2_x(x, y);
}

s32 bgmap_init(s16 arg, s32 state)
{
    size_t len;
    uint i;
    bgmap = &bgmap_table[arg];
    len = BGMAP_H*bgmap->w;
    bgmap_img[0] = mem_alloc_l(sizeof(u16) * BGMAP_TN*len);
    for (i = 0; i < BGMAP_TN-1; i++)
    {
        bgmap_img[i+1] = bgmap_img[i] + len;
    }
    for (i = 0; i < BGMAP_TN; i++)
    {
        bgmap_pos[i] = -1;
    }
    bgmap_offset = 0;
    return course_init(arg, state);
}

static int bgmap_update_link(f32 *pos)
{
    uint index;
    while (true)
    {
        const struct bgmap_link_t *link;
        int x;
        index = (uint)((int)pos[1]+6880) / 4096;
        if (index >= 3)
        {
            print_int(20, 20, "bad %d", pos[1]);
            break;
        }
        link = &bgmap->link[index];
        x = pos[0];
        if (x < link->xl)
        {
            pos[0] += link[-1].org - link[0].org;
            pos[1] -= 4096;
            continue;
        }
        if (x > link->xh)
        {
            pos[0] += link[ 1].org - link[0].org;
            pos[1] += 4096;
            continue;
        }
        break;
    }
    return index;
}

Gfx *bgmap_g_main(int mode, struct gc_t *gc, void *data)
{
    if (mode == 1)
    {
        Mtx *m;
        struct gc_camera_t *gc_camera;
        struct camera_t *camera;
        struct player_t *player;
        struct object_t *object;
        int  y;
        uint index;
        f32  o;
        f32  t;
        uint x;
        uint n;
        uint i;
        m = mem_alloc_gfx(sizeof(*m));
        guOrtho(m, -640, 640, -480, 480, -8192, 8192, 1);
        gSPPerspNormalize(video_gfx++, 0xFFFF);
        gSPMatrix(video_gfx++, m, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gc_camera = (struct gc_camera_t *)gc;
        camera = (struct camera_t *)gc->arg;
        player = &game_player_table[0];
        player->pos[2] = 32;
        player->object->go.pos[2] = 32;
        y = player->pos[1];
        if (bgmap_out(y, 0) || bgmap_out(y, 1) || bgmap_out(y, 2))
        {
            course_out();
        }
        object = course_object();
        index = bgmap_update_link(player->pos);
        i = bgmap_update_link(&object->o_pos_x);
        if (object->o_opponent_path == NULL)
        {
            object->o_opponent_path = mem_segment(bgmap->link[i].path);
        }
        if (course_lose())
        {
            index = i;
            o = object->o_pos_x - player->pos[0];
            o -= bgmap_offset;
            if (o > 1024)
            {
                o = 1024;
            }
            else
            {
                course_latch();
            }
            bgmap_offset += (1.0F/16.0F) * o;
        }
        else if (course_lock())
        {
            bgmap_offset = 0;
        }
        else
        {
            if (player->pad->down & (L_CBUTTONS | R_CBUTTONS | R_TRIG))
            {
                audio_sfx_play(SFX_SYS_CAMMOVE, audio_sfx_org);
            }
            if (player->pad->held & L_CBUTTONS)
            {
                o = -0x1C0;
            }
            else if (player->pad->held & (R_CBUTTONS | R_TRIG))
            {
                o =  0x1C0;
            }
            else
            {
                o = 4*player->vel[0] + 128*sin(player->rot[1]);
            }
            bgmap_offset += (1.0F/16.0F) * (o-bgmap_offset);
        }
        o = player->pos[0] + bgmap_offset;
        t = bgmap->link[index].t;
        if (o < t)
        {
            o = t;
        }
        gc_camera->pos[0] = o;
        gc_camera->obj[0] = o;
        gc_camera->pos[1] = (0x100-4096) + 4096*(signed)index;
        gc_camera->obj[1] = (-0x30-4096) + 4096*(signed)index;
        gc_camera->pos[2] = 0x400;
        gc_camera->obj[2] = 0;
        camera->yaw       = 0x0000;
        camera->mode_demo = 0x80;
        x = (int)(o - t);
        gSPDisplayList(video_gfx++, gfx_course_start);
        bgmap->callback(x);
        n = x / BGMAP_MH;
        for (i = 0; i < BGMAP_TN; i++)
        {
            uint map = n % BGMAP_TN;
            if (bgmap_pos[map] != n && n < bgmap->szp_max)
            {
                bgmap_pos[map] = n;
                mem_dma_read(
                    bgmap_szp, bgmap->szp_table[n+0], bgmap->szp_table[n+1]
                );
                szp_decode(bgmap_szp, bgmap_img[map]);
            }
            bgmap_draw(
                bgmap_img[map], bgmap->w, BGMAP_H, BGMAP_MH*bgmap_pos[map]-x,
                bgmap->y
            );
            n++;
        }
        gSPDisplayList(video_gfx++, gfx_course_end);
        return NULL;
    }
    return camera_g_camera(mode, gc, data);
}
