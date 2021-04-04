/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#ifndef _SM64_H_
#define _SM64_H_

#include <ultra64.h>

#define G_R_BACKGROUND          0x00
#define G_R_OPA_SURF            0x01
#define G_R_OPA_DECAL           0x02
#define G_R_OPA_INTER           0x03
#define G_R_SPRITE              0x04
#define G_R_XLU_SURF            0x05
#define G_R_XLU_DECAL           0x06
#define G_R_XLU_INTER           0x07

#define G_O_KOOPA               0x68

#ifndef __ASSEMBLER__

#define PLAYER_STATE_NULL       0x00000000
#define PLAYER_STATE_IDLE       0x0C400201
#define PLAYER_STATE_WAITMSG    0x0000130A
#define PLAYER_STATE_SPAWNAIR   0x00001932

#define PLAYER_MOTION_MESSAGE   0xC2
#define PLAYER_MOTION_WINDEMO   0xCD

#define HUD_LIFE                0x0001
#define HUD_COIN                0x0002
#define HUD_STAR                0x0004
#define HUD_POWER               0x0008
#define HUD_KEY                 0x0010
#define HUD_0020                0x0020
#define HUD_TIME                0x0040

#define SFX_GS1_GUNSHOT         0x314D4081
#define SFX_GS1_CORRECT         0x306A8081
#define SFX_SYS_CAMMOVE         0x700F0081
#define SFX_SYS_START           0x701EFF81

#define game_timer_show()       game_timer_main(0)
#define game_timer_start()      game_timer_main(1)
#define game_timer_stop()       game_timer_main(2)
#define game_timer_hide()       game_timer_main(3)
#define game_timer_value()      game_timer_main(4)

#define mem_alloc_l(size)       mem_alloc(size, 0)
#define mem_alloc_r(size)       mem_alloc(size, 1)

#define menu_scroll_v(index, min, max)  menu_scroll(1, index, min, max)
#define menu_scroll_h(index, min, max)  menu_scroll(2, index, min, max)

#define sin(x)  math_sin[(u16)(x) >> 4]
#define cos(x)  math_cos[(u16)(x) >> 4]

#define o_pos_x                 mem[0x06].f32
#define o_pos_y                 mem[0x07].f32
#define o_pos_z                 mem[0x08].f32
#define o_vel_x                 mem[0x09].f32
#define o_vel_y                 mem[0x0A].f32
#define o_vel_z                 mem[0x0B].f32
#define o_vel_f                 mem[0x0C].f32
#define o_vel_l                 mem[0x0D].f32
#define o_vel_u                 mem[0x0E].f32
#define o_rot_x                 mem[0x0F].s32
#define o_rot_y                 mem[0x10].s32
#define o_rot_z                 mem[0x11].s32
#define o_rot_gfx_x             mem[0x12].s32
#define o_rot_gfx_y             mem[0x13].s32
#define o_rot_gfx_z             mem[0x14].s32
#define o_move_flag             mem[0x19].u32
#define o_path_rx               mem[0x20].s32
#define o_path_ry               mem[0x21].s32
#define o_motion_table          mem[0x26].ptr
#define o_state                 mem[0x31].s32
#define o_mode                  mem[0x32].s32

struct pad_t
{
    /* 0x00 */  s16     stick_x;
    /* 0x02 */  s16     stick_y;
    /* 0x04 */  f32     stick[2];
    /* 0x0C */  f32     stick_mag;
    /* 0x10 */  u16     held;
    /* 0x12 */  u16     down;
    /* 0x14 */  void   *pad;
    /* 0x18 */  void   *status;
};  /* 0x1C */

struct g_t
{
    /* 0x00 */  u16 type;
    /* 0x02 */  u16 flags;
    /* 0x04 */  struct g_t *prev;
    /* 0x08 */  struct g_t *next;
    /* 0x0C */  struct g_t *parent;
    /* 0x10 */  struct g_t *child;
};  /* 0x14 */

struct gc_t
{
    /* 0x00 */  struct g_t g;
    /* 0x14 */  Gfx *(*callback)(int, struct gc_t *, void *);
    /* 0x18 */  s32 arg;
};  /* 0x1C */

struct g_motion_t
{
    /* 0x00 0x38 */ s16     index;
    /* 0x02 0x3A */ s16     height;
    /* 0x04 0x3C */ struct motion_t *motion;
    /* 0x08 0x40 */ s16     frame;
    /* 0x0A 0x42 */ u16     timer;
    /* 0x0C 0x44 */ s32     frame_amt;
    /* 0x10 0x48 */ s32     frame_vel;
};  /* 0x14 0x4C */

struct g_object_t
{
    /* 0x00 */  struct g_t g;
    /* 0x14 */  struct g_t *list;
    /* 0x18 */  s8      world_index;
    /* 0x19 */  s8      gfx_index;
    /* 0x1A */  s16     rot[3];
    /* 0x20 */  f32     pos[3];
    /* 0x2C */  f32     scale[3];
    /* 0x38 */  struct g_motion_t motion;
    /* 0x4C */  void   *_4C;
    /* 0x50 */  f32   (*mtxf)[4][4];
    /* 0x54 */  f32     pos_sfx[3];
};  /* 0x60 */

struct gc_camera_t
{
    /* 0x00 */  struct gc_t gc;
    /* 0x1C */  f32     pos[3];
    /* 0x28 */  f32     obj[3];
    /* 0x34 */  f32   (*mtxf)[4][4];
    /* 0x38 */  s16     rot_z_m;
    /* 0x3A */  s16     rot_z_p;
};  /* 0x3C */

struct camera_t
{
    /* 0x00 */  u8      mode;
    /* 0x01 */  u8      mode_prev;
    /* 0x02 */  s16     yaw;
    /* 0x04 */  f32     obj[3];
    /* 0x10 */  f32     pos[3];
    /* 0x1C */  s16     rot[3];
    /* 0x22 */  s16     _22[3];
    /* 0x28 */  f32     _28;
    /* 0x2C */  f32     _2C;
    /* 0x30 */  u8      mode_demo;
    /* 0x34 */  f32     _34;
    /* 0x38 */  s8      _38;
    /* 0x3A */  s16     _3A;
    /* 0x3C */  s16     _3C;
    /* 0x3E */
};

struct object_t
{
    /* 0x0000 */    struct g_object_t go;
    /* 0x0060 */    struct object_t *next;
    /* 0x0064 */    struct object_t *prev;
    /* 0x0068 */    struct object_t *parent;
    /* 0x006C */    struct object_t *child;
    /* 0x0070 */    u32     touch;
    /* 0x0074 */    s16     flag;
    /* 0x0076 */    s16     object_touch_len;
    /* 0x0078 */    struct object_t *object_touch[4];
    /* 0x0088 */    union
                    {
                        s8      s8[4];
                        u8      u8[4];
                        s16     s16[2];
                        u16     u16[2];
                        s32     s32;
                        u32     u32;
                        f32     f32;
                        void   *ptr;
                    }
                    mem[80];
    /* 0x01C8 */    void   *_1C8;
    /* 0x01CC */    uintptr_t *pc;
    /* 0x01D0 */    uintptr_t stack_index;
    /* 0x01D4 */    uintptr_t stack[8];
    /* 0x01F4 */    s16     _1F4;
    /* 0x01F6 */    s16     _1F6;
    /* 0x01F8 */    f32     _1F8;
    /* 0x01FC */    f32     _1FC;
    /* 0x0200 */    f32     _200;
    /* 0x0204 */    f32     _204;
    /* 0x0208 */    f32     _208;
    /* 0x020C */    uintptr_t *script;
    /* 0x0210 */    struct object_t *_210;
    /* 0x0214 */    struct object_t *_214;
    /* 0x0218 */    s16    *_218;
    /* 0x021C */    f32     mtxf[4][4];
    /* 0x025C */    void   *_25C;
};  /* 0x0260 */

struct player_gfx_t
{
    /* 0x00 */  u32     state;
    /* 0x04 */  s8      head;
    /* 0x05 */  s8      eyes;
    /* 0x06 */  s8      gloves;
    /* 0x07 */  s8      wings;
    /* 0x08 */  s16     cap;
    /* 0x0A */  s8      hold;
    /* 0x0B */  u8      punch;
    /* 0x0C */  s16     rot_torso[3];
    /* 0x12 */  s16     rot_head[3];
    /* 0x18 */  f32     pos_glove[3];
    /* 0x24 */  struct object_t *object;
};  /* 0x28 */

struct player_t
{
    /* 0x00 */  u16     index;
    /* 0x02 */  u16     event;
    /* 0x04 */  u32     flag;
    /* 0x08 */  u32     particle;
    /* 0x0C */  u32     state;
    /* 0x10 */  u32     state_prev;
    /* 0x14 */  u32     ground_sfx;
    /* 0x18 */  s16     state_mode;
    /* 0x1A */  u16     state_timer;
    /* 0x1C */  u32     state_arg;
    /* 0x20 */  f32     stick_mag;
    /* 0x24 */  s16     stick_rot;
    /* 0x26 */  s16     timer_invincible;
    /* 0x28 */  u8      timer_a_down;
    /* 0x29 */  u8      timer_b_down;
    /* 0x2A */  u8      timer_col_wall;
    /* 0x2B */  u8      timer_col_floor;
    /* 0x2C */  s16     rot[3];
    /* 0x32 */  s16     rot_vel[3];
    /* 0x38 */  s16     rot_slide;
    /* 0x3A */  s16     rot_twirl;
    /* 0x3C */  f32     pos[3];
    /* 0x48 */  f32     vel[3];
    /* 0x54 */  f32     vel_f;
    /* 0x58 */  f32     vel_h[2];
    /* 0x60 */  void   *wall;
    /* 0x64 */  void   *roof;
    /* 0x68 */  void   *ground;
    /* 0x6C */  f32     height_roof;
    /* 0x70 */  f32     height_ground;
    /* 0x74 */  s16     rot_ground;
    /* 0x76 */  s16     height_water;
    /* 0x78 */  struct object_t *object_touch;
    /* 0x7C */  struct object_t *object_hold;
    /* 0x80 */  struct object_t *object_use;
    /* 0x84 */  struct object_t *object_ride;
    /* 0x88 */  struct object_t *object;
    /* 0x8C */  void   *_8C;
    /* 0x90 */  void   *world;
    /* 0x94 */  void   *camera;
    /* 0x98 */  struct player_gfx_t *gfx;
    /* 0x9C */  struct pad_t *pad;
    /* 0xA0 */  struct motion_t *motion;
    /* 0xA4 */  u32     touch;
    /* 0xA8 */  s16     coin;
    /* 0xAA */  s16     star;
    /* 0xAC */  s8      key;
    /* 0xAD */  s8      life;
    /* 0xAE */  s16     health;
    /* 0xB0 */  s16     motion_height;
    /* 0xB2 */  u8      timer_power_dec;
    /* 0xB3 */  u8      timer_power_inc;
    /* 0xB4 */  u8      timer_squish;
    /* 0xB5 */  u8      timer_dither;
    /* 0xB6 */  u16     timer_cap;
    /* 0xB8 */  s16     star_prev;
    /* 0xBC */  f32     height_peak;
    /* 0xC0 */  f32     height_sink;
    /* 0xC4 */  f32     gravity;
};  /* 0xC8 */

struct hud_t
{
    /* 0x00 */  s16     lives;
    /* 0x02 */  s16     coins;
    /* 0x04 */  s16     stars;
    /* 0x06 */  s16     power;
    /* 0x08 */  s16     keys;
    /* 0x0A */  s16     flag;
    /* 0x0C */  u16     timer;
};  /* 0x0E */

/* 0x802473C8 */ extern void  app_gfx_start_cimg(void);
/* 0x80247D14 */ extern void  app_gfx_end(void);
/* 0x802495E0 */ extern u16   game_timer_main(int mode);
/* 0x80249764 */ extern void  game_state_set(s16 state);
/* 0x8024978C */ extern void  game_state_end(int arg);
/* 0x802497B8 */ extern void  game_state_end_wipe(int arg, uint shade);
/* 0x8024A700 */ extern void  game_link(
    s16 stage, s16 world, s16 link, uint arg
);
/* 0x8024BCD8 */ extern s32   game_main(s16 arg, s32 state);
/* 0x802509B8 */ extern s32   player_motion_set(
    struct player_t *player, s32 motion
);
/* 0x80252CF4 */ extern u32   player_state_set(
    struct player_t *player, u32 state, u32 arg
);
/* 0x80277F50 */ extern void *mem_segment(const void *);
/* 0x80278120 */ extern void *mem_alloc(size_t size, uint side);
/* 0x80278120 */ extern void  mem_free(void *ptr);
/* 0x80278504 */ extern void  mem_dma_read(
    void *dst, const void *start, const void *end
);
/* 0x80278F2C */ extern void *mem_alloc_gfx(size_t size);
/* 0x8027B0C0 */ extern void  world_set(int world);
/* 0x8027B1A0 */ extern void  world_wipe(s16 type, s16 time, u8 r, u8 g, u8 b);
/* 0x8027B35C */ extern void  world_wipe_delay(
    s16 type, s16 time, u8 r, u8 g, u8 b, s16 delay
);
/* 0x8027F4E0 */ extern s32   szp_decode(const void *src, void *dst);
/* 0x80287D30 */ extern Gfx  *camera_g_camera(
    int mode, struct gc_t *gc, void *data
);
/* 0x8029AA3C */ extern Gfx  *camera_g_persp(
    int mode, struct gc_t *gc, void *data
);
/* 0x8029E5EC */ extern void  object_turn_ry(s16 dst, s16 d);
/* 0x8029ED20 */ extern struct object_t *object_init(
    const struct object_t *parent,
    uint a1,
    uint gfx,
    const uintptr_t *script
);
/* 0x8029F4B4 */ extern void  object_motion(uint motion);
/* 0x8029F514 */ extern void  object_motion_vel(uint, f32);
/* 0x8029F9EC */ extern struct object_t *object_find_distance(
    const uintptr_t *script, f32 *distance
);
/* 0x802FA360 */ extern uint  object_motion_end(uint motion);
/* 0x802FA428 */ extern void  object_motion_sfx_foot(s8 l, s8 r, u32 sfx);
/* 0x802A2320 */ extern void  object_map(void);
/* 0x802A2348 */ extern void  object_move(s16);
/* 0x802D62D8 */ extern void  print_int(s16 x, s16 y, const char *fmt, int i);
/* 0x802D6554 */ extern void  print(s16 x, s16 y, const char *str);
/* 0x802D7384 */ extern void  menu_ortho(void);
/* 0x802D862C */ extern void  menu_scroll(s8 dir, s8 *index, s8 min, s8 max);
/* 0x802FA5D0 */ extern void  object_move_vel_f(f32 dst, f32 d);
/* 0x802FA748 */ extern void  object_turn_gfx_ry(s16 dst, s16 d);
/* 0x802FAD34 */ extern void  object_blink(s32 *, s16, s16, s16);
/* 0x8031EB00 */ extern void  audio_sfx_play(u32, f32[3]);
/* 0x8037A9A8 */ extern s16   atan2(f32 y, f32 x);
/* 0x8037C658 */ extern void  gfx_object_motion(
    struct g_object_t *go, const struct motion_t *const *motion
);

/* 0x8032D58C */ extern bool main_debug_stage;
/* 0x8032D598 */ extern bool main_debug_mem;
/* 0x8032D5D4 */ extern u32  app_frame;
/* 0x8032D5DC */ extern u16  app_cimg_dl;
/* 0x8032D5E4 */ extern struct pad_t *app_pad_1;
/* 0x8032D5E8 */ extern struct pad_t *app_pad_2;
/* 0x8032D5EC */ extern struct pad_t *app_pad_menu;
/* 0x8032DD98 */ extern s8   save_course_table[38];
/* 0x8032DDF8 */ extern s16  world_stage;
/* 0x803331F0 */ extern f32  audio_sfx_org[3];
/* 0x8033B050 */ extern u16 *video_cimg[3];
/* 0x8033B06C */ extern Gfx *video_gfx;
/* 0x8033B170 */ extern struct player_t game_player_table[1];
/* 0x8033B260 */ extern struct hud_t hud;
/* 0x8033BACA */ extern s16  world_index;
/* 0x8033CBD0 */ extern struct camera_t *camera_ptr;
/* 0x80361160 */ extern struct object_t *object_ptr;

/* 0x80386000 */ extern f32 math_sin[];
/* 0x80387000 */ extern f32 math_cos[];

/* 0x1300091C */ extern const uintptr_t o_coin[];
/* 0x13003EAC */ extern const uintptr_t o_redcoin[];

#define M_VTX                   0x0040
#define M_BREAK                 0x0041
#define M_END                   0x0042
#define M_OBJ                   0x0043
#define M_WATER                 0x0044

#define M_O_COIN                0x0001

#define S_O_END                 0x01E
#define S_O_COIN                0x01F
#define S_O_REDCOIN             0x023
#define S_O_CORKBOX             0x064
#define S_O_CORKBOXCOIN         0x065
#define S_O_METALBOX            0x065
#define S_O_SMALLBOX            0x067

#define _C(c, x, y) ((u32)(u8)(c) << 24 | (u32)(u8)(x) << 16 | (u32)(u16)(y))
#define _H(x, y)    ((u32)(u16)(x) << 16 | (u32)(u16)(y))
#define _W(x)       ((u32)(x))
#define _F(x)       ((u32)(0x10000*(x)))
#define _P(x)       ((uintptr_t)(x))

/* 0x00 */
#define g_exit()                                \
    _C(0x01, 0, 0)
#define g_jump(script)                          \
    _C(0x02, 0, 0),                             \
    _P(script)
#define g_call(script)                          \
    _C(0x02, 1, 0),                             \
    _P(script)
#define g_return()                              \
    _C(0x03, 0, 0)
#define g_start()                               \
    _C(0x04, 0, 0)
#define g_end()                                 \
    _C(0x05, 0, 0)
/* 0x06 */
/* 0x07 */
#define g_world(x, y, w, h, n)                  \
    _C(0x08, 0, n),                             \
    _H(x, y),                                   \
    _H(w, h)
#define g_ortho(scale)                          \
    _C(0x09, 0, scale)
#define g_persp(fovy, n, f)                     \
    _C(0x0A, 0, fovy),                          \
    _H(n, f)
#define g_perspective(fovy, n, f, callback)     \
    _C(0x0A, 1, fovy),                          \
    _H(n, f),                                   \
    _P(callback)
#define g_empty()                               \
    _C(0x0B, 0, 0)
#define g_layer(depth)                          \
    _C(0x0C, depth, 0)
/* 0x0D */
#define g_select(arg, callback)                 \
    _C(0x0E, 0, arg),                           \
    _P(callback)
#define g_camera(arg, px, py, pz, lx, ly, lz, callback)    \
    _C(0x0F, 0, arg),                           \
    _H(px, py),                                 \
    _H(pz, lx),                                 \
    _H(ly, lz),                                 \
    _P(callback)
#define g_posrot(px, py, pz, rx, ry, rz)        \
    _C(0x10, 0, 0),                             \
    _H(px, py),                                 \
    _H(pz, rx),                                 \
    _H(ry, rz)
/* 0x11 */
#define g_gfx_pos(rm, gfx, px, py, pz)          \
    _C(0x11, 0x80 | G_R_##rm, px),              \
    _H(py, pz),                                 \
    _P(gfx)
#define g_rot(rx, ry, rz)                       \
    _C(0x12, 0, rx),                            \
    _H(ry, rz)
#define g_joint(rm, gfx, px, py, pz)            \
    _C(0x13, G_R_##rm, px),                     \
    _H(py, pz),                                 \
    _P(gfx)
/* 0x14 */
#define g_gfx(rm, gfx)                          \
    _C(0x15, G_R_##rm, 0),                      \
    _P(gfx)
#define g_shadow(scale, alpha, type)            \
    _C(0x16, 0, type),                          \
    _H(alpha, scale)
#define g_object()                              \
    _C(0x17, 0, 0)
#define g_callback(arg, callback)               \
    _C(0x18, 0, arg),                           \
    _P(callback)
#define g_background(arg, callback)             \
    _C(0x19, 0, arg),                           \
    _P(callback)
/* 0x1A */
/* 0x1B */
#define g_hand(px, py, pz, arg, callback)       \
    _C(0x1C, arg, px),                          \
    _H(py, pz),                                 \
    _P(callback)
#define g_scale(scale)                          \
    _C(0x1D, 0, 0),                             \
    _F(scale)
/* 0x1E */
/* 0x1F */
/* 0x20 */

#else /* __ASSEMBLER__ */

#define _B(c, x, y, z)      .byte (c), (x), (y), (z)
#define _C(c, x, y)         .byte (c), (x); .hword (y)
#define _H(x, y)            .hword (x), (y)
#define _W(x)               .word (x)
#define _F(x)               .float (x)
#define _P(x)               .word (x)

#define S_C_AND             0x00
#define S_C_NAND            0x01
#define S_C_EQ              0x02
#define S_C_NE              0x03
#define S_C_GT              0x04
#define S_C_GE              0x05
#define S_C_LT              0x06
#define S_C_LE              0x07

#define S_V_SAVE            0x00
#define S_V_COURSE          0x01
#define S_V_LEVEL           0x02
#define S_V_STAGE           0x03
#define S_V_WORLD           0x04

#define s_scall(seg, name)                      \
    _C(0x00, 0x10, seg);                        \
    _P(scr_##name##_start);                     \
    _P(scr_##name##_end);                       \
    _P(s_##name)
#define s_sjump(seg, name)                      \
    _C(0x01, 0x10, seg);                        \
    _P(scr_##name##_start);                     \
    _P(scr_##name##_end);                       \
    _P(s_##name)
#define s_sreturn()                             \
    _C(0x02, 0x04, 0)
#define s_sleep(x)                              \
    _C(0x03, 0x04, x)
#define s_freeze(x)                             \
    _C(0x04, 0x04, x)
#define s_jump(script)                          \
    _C(0x05, 0x08, 0);                          \
    _P(script)
#define s_call(script)                          \
    _C(0x06, 0x08, 0);                          \
    _P(script)
#define s_return()                              \
    _C(0x07, 0x04, 0)
/* 0x08 */
/* 0x09 */
#define s_do()                                  \
    _C(0x0A, 0x04, 0)
/* 0x0B */
#define s_while(c, val)                         \
    _B(0x0B, 0x08, S_C_##c, 0);                 \
    _W(val);
#define s_cjump(c, val, script)                 \
    _B(0x0C, 0x0C, S_C_##c, 0);                 \
    _W(val);                                    \
    _P(script)
#define s_ccall(c, val, script)                 \
    _B(0x0D, 0x0C, S_C_##c, 0);                 \
    _W(val);                                    \
    _P(script)
/* 0x0E */
/* 0x0F */
/* 0x10 */
#define s_callback(callback, arg)               \
    _C(0x11, 0x08, arg);                        \
    _P(callback)
#define s_update(callback, arg)                 \
    _C(0x12, 0x08, arg);                        \
    _P(callback)
#define s_set(val)                              \
    _C(0x13, 0x04, val)
#define s_mem_push()                            \
    _C(0x14, 0x04, 0)
#define s_mem_pop()                             \
    _C(0x15, 0x04, 0)
#define s_read_code(dst, name)                  \
    _C(0x16, 0x10, 0);                          \
    _P(dst);                                    \
    _P(name##_start);                           \
    _P(name##_end)
#define s_read_scr(seg, name)                   \
    _C(0x17, 0x0C, seg);                        \
    _P(scr_##name##_start);                     \
    _P(scr_##name##_end)
#define s_read_szp(seg, name)                   \
    _C(0x18, 0x0C, seg);                        \
    _P(szp_##name##_start);                     \
    _P(szp_##name##_end)
#define s_read_face(arg)                        \
    _C(0x19, 0x04, arg)
#define s_read_tex(seg, name)                   \
    _C(0x1A, 0x0C, seg);                        \
    _P(szp_##name##_start);                     \
    _P(szp_##name##_end)
#define s_stage_init()                          \
    _C(0x1B, 0x04, 0)
#define s_stage_destroy()                       \
    _C(0x1C, 0x04, 0)
#define s_compile_start()                       \
    _C(0x1D, 0x04, 0)
#define s_compile_end()                         \
    _C(0x1E, 0x04, 0)
#define s_world_start(index, script)            \
    _B(0x1F, 0x08, index, 0);                   \
    _P(script)
#define s_world_end()                           \
    _C(0x20, 0x04, 0)
#define s_g_gfx(index, gfx, rm)                 \
    _C(0x21, 0x08, G_R_##rm << 12 | (index));   \
    _P(gfx)
#define s_g_scr(index, script)                  \
    _C(0x22, 0x08, index);                      \
    _P(script)
#define s_g_scale(index, gfx, rm, scale)        \
    _C(0x23, 0x08, G_R_##rm << 12 | (index));   \
    _P(gfx);                                    \
    _F(scale)
#define s_object(mask, g, px, py, pz, rx, ry, rz, arg0, arg1, flag, script) \
    _B(0x24, 0x18, mask, g);                    \
    _H(px, py);                                 \
    _H(pz, rx);                                 \
    _H(ry, rz);                                 \
    _C(arg0, arg1, flag);                       \
    _P(script)
#define s_object_all(g, px, py, pz, rx, ry, rz, arg0, arg1, flag, script)   \
    s_object(0x1F, g, px, py, pz, rx, ry, rz, arg0, arg1, flag, script)
#define s_player(index, g, arg, script)         \
    _B(0x25, 0x0C, index, g);                   \
    _W(arg);                                    \
    _P(script)
#define s_mario()                               \
    s_player(0, 0x01, 1, o_mario)
#define s_luigi(g, arg, script)                 \
    s_player(1, g, arg, script)
#define s_link(index, stage, world, link)       \
    _B(0x26, 0x08, index, stage);               \
    _B(world, link, 0x00, 0)
#define s_link_mid(index, stage, world, link)   \
    _B(0x26, 0x08, index, stage);               \
    _B(world, link, 0x80, 0)
/* 0x27 link_bg */
#define s_link_world(n, world, px, py, pz)      \
    _B(0x28, 0x0C, n, world);                   \
    _H(px, py);                                 \
    _H(pz, 0)
#define s_world_init(world)                     \
    _B(0x29, 0x04, world, 0)
#define s_world_destroy(world)                  \
    _B(0x2A, 0x04, world, 0)
#define s_player_init(index, w, ry, px, py, pz) \
    _B(0x2B, 0x0C, w, index);                   \
    _H(ry, px);                                 \
    _H(py, pz)
#define s_mario_init(w, ry, px, py, pz)         \
    s_player_init(0, w, ry, px, py, pz)
#define s_luigi_init(w, ry, px, py, pz)         \
    s_player_init(1, w, ry, px, py, pz)
/* 0x2C player_destroy */
#define s_world_update()                        \
    _C(0x2D, 0x08, 0)
#define s_world_map(map)                        \
    _C(0x2E, 0x08, 0);                          \
    _P(map)
/* 0x2F world_area */
/* 0x30 world_message */
#define s_world_env(env)                        \
    _C(0x31, 0x04, env)
/* 0x32 */
#define s_wipe(type, time, r, g, b)             \
    _B(0x33, 0x08, type, time);                 \
    _B(r, g, b, 0)
#define s_vi_black(arg)                         \
    _B(0x34, 0x04, arg, 0)
#define s_vi_gamma(arg)                         \
    _B(0x35, 0x04, arg, 0)
#define s_world_music(type, music)              \
    _C(0x36, 0x08, type);                       \
    _H(music, 0)
#define s_music_play(music)                     \
    _C(0x37, 0x04, music)
/* 0x38 music_stop */
#define s_world_obj(obj)                        \
    _C(0x39, 0x08, 0);                          \
    _P(obj)
/* 0x3A world_wind */
/* 0x3B world_jet */
#define s_write(var)                            \
    _B(0x3C, 0x04, 0, S_V_##var)
#define s_read(var)                             \
    _B(0x3C, 0x04, 1, S_V_##var)

#define O_T_PLAYER              0x00
#define O_T_01                  0x01
#define O_T_PLAYERATTACK        0x02
#define O_T_03                  0x03
#define O_T_OBJECTA             0x04
#define O_T_OBJECTB             0x05
#define O_T_ITEM                0x06
#define O_T_07                  0x07
#define O_T_DEFAULT             0x08
#define O_T_MOVEBG              0x09
#define O_T_PLAYERUSE           0x0A
#define O_T_SYSTEM              0x0B
#define O_T_PARTICLE            0x0C

#define O_M_FLAG                0x01
#define O_M_MOTION              0x26

#define o_init(type)                            \
    _C(0x00, O_T_##type, 0)
#define o_sleep(count)                          \
    _C(0x01, 0, count)
#define o_call(script)                          \
    _C(0x02, 0, 0);                             \
    _P(script)
#define o_return()                              \
    _C(0x03, 0, 0)
#define o_jump(script)                          \
    _C(0x04, 0, 0);                             \
    _P(script)
#define o_for(count)                            \
    _C(0x05, 0, count)
#define o_fend()                                \
    _C(0x06, 0, 0)
#define o_fnext()                               \
    _C(0x07, 0, 0)
#define o_while()                               \
    _C(0x08, 0, 0)
#define o_wend()                                \
    _C(0x09, 0, 0)
#define o_exit()                                \
    _C(0x0A, 0, 0)
#define o_exit2()                               \
    _C(0x0B, 0, 0)
#define o_callback(callback)                    \
    _C(0x0C, 0, 0);                             \
    _P(callback)
#define o_addf(mem, val)                        \
    _C(0x0D, O_M_##mem, val)
#define o_setf(mem, val)                        \
    _C(0x0E, O_M_##mem, val)
#define o_addi(mem, val)                        \
    _C(0x0F, O_M_##mem, val)
#define o_seti(mem, val)                        \
    _C(0x10, O_M_##mem, val)
#define o_setflag(mem, val)                     \
    _C(0x11, O_M_##mem, val)
#define o_clrflag(mem, val)                     \
    _C(0x12, O_M_##mem, val)
#define o_setrandr(mem, val, shift)             \
    _C(0x13, O_M_##mem, val);                   \
    _H(shift, 0)
#define o_setrandf(mem, val, mul)               \
    _C(0x14, O_M_##mem, val);                   \
    _H(mul, 0)
#define o_setrandi(mem, val, mul)               \
    _C(0x15, O_M_##mem, val);                   \
    _H(mul, 0)
#define o_addrandf(mem, val, mul)               \
    _C(0x16, O_M_##mem, val);                   \
    _H(mul, 0)
#define o_addrandr(mem, val, shift)             \
    _C(0x17, O_M_##mem, val);                   \
    _H(shift, 0)
/* 0x18 */
/* 0x19 */
/* 0x1A */
#define o_gfx(mem, gfx)                         \
    _C(0x1B, O_M_##mem, gfx)
#define o_object(gfx, script)                   \
    _C(0x1C, 0, 0);                             \
    _W(gfx);                                    \
    _P(script)
#define o_destroy()                             \
    _C(0x1D, 0, 0)
#define o_ground()                              \
    _C(0x1E, 0, 0)
#define o_memaddf(mem, a, b)                    \
    _B(0x1F, O_M_##mem, O_M_##a, O_M_##b)
#define o_memaddi(mem, a, b)                    \
    _B(0x20, O_M_##mem, O_M_##a, O_M_##b)
#define o_billboard()                           \
    _C(0x21, 0, 0)
#define o_gfxhide()                             \
    _C(0x22, 0, 0)
#define o_hitbox(radius, height)                \
    _C(0x23, 0, 0);                             \
    _H(radius, height)
/* 0x24 */
#define o_memsleep(mem)                         \
    _C(0x25, O_M_##mem, 0)
#define o_memfor(mem)                           \
    _C(0x26, O_M_##mem, 0)
#define o_ptr(mem, ptr)                         \
    _C(0x27, O_M_##mem, 0);                     \
    _P(ptr)
#define o_motion(motion)                        \
    _C(0x28, motion, 0)
#define o_objectarg(gfx, script, arg)           \
    _C(0x29, 0, arg);                           \
    _W(gfx);                                    \
    _P(script)
#define o_map(map)                              \
    _C(0x2A, 0, 0);                             \
    _P(map)
#define o_hitboxoffset(radius, height, offset)  \
    _C(0x2B, 0, 0);                             \
    _H(radius, height);                         \
    _H(offset, 0)
#define o_child(gfx, script)                    \
    _C(0x2C, 0, 0);                             \
    _W(gfx);                                    \
    _P(script)
#define o_origin()                              \
    _C(0x2D, 0, 0)
#define o_hurtbox(radius, height)               \
    _C(0x2E, 0, 0);                             \
    _H(radius, height)
#define o_touch(touch)                          \
    _C(0x2F, 0, 0);                             \
    _W(touch)
#define o_move(a, b, c, d, e, f, g, h)          \
    _C(0x30, 0, 0);                             \
    _H(a, b);                                   \
    _H(c, d);                                   \
    _H(e, f);                                   \
    _H(g, h)
#define o_touchtype(type)                       \
    _C(0x31, 0, 0);                             \
    _W(type)
#define o_scale(scale)                          \
    _C(0x32, 0, scale)
#define o_memclrflag(mem, flag)                 \
    _C(0x33, O_M_##mem, 0);                     \
    _W(flag)
#define o_inc(mem, frame)                       \
    _C(0x34, O_M_##mem, frame)
#define o_gfxdisable()                          \
    _C(0x35, 0, 0)
#define o_sets(mem, val)                        \
    _C(0x36, 0, 0);                             \
    _W(val)
#define o_objectdata(data)                      \
    _C(0x37, 0, 0);                             \
    _P(data)

#endif /* __ASSEMBLER__ */

#endif /* _SM64_H_ */
