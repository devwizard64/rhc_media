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

#ifndef _SCRIPT

#define C_A0    0x29, 0x5A, 0xFF    /* 0x28, 0x58, 0xF8 */
#define C_A1    0x4A, 0x73, 0xFF    /* 0x48, 0x70, 0xF8 */
#define C_A2    0x62, 0x83, 0xFF    /* 0x60, 0x80, 0xF8 */
#define C_B0    0xAC, 0xCD, 0xFF    /* 0xA8, 0xC8, 0xF8 */
#define C_B1    0xBD, 0xDE, 0xFF    /* 0xB8, 0xD8, 0xF8 */
#define C_B2    0xD5, 0xEE, 0xFF    /* 0xD0, 0xE8, 0xF8 */

#define VTX(y, c)                                                              \
    {{{COURSE_TILE_S*0, COURSE_TILE_S*((y)+0), 0}, 0, {0, 0}, {C_##c##0, 0}}}, \
    {{{COURSE_TILE_S*1, COURSE_TILE_S*((y)+0), 0}, 0, {0, 0}, {C_##c##1, 0}}}, \
    {{{COURSE_TILE_S*1, COURSE_TILE_S*((y)+1), 0}, 0, {0, 0}, {C_##c##2, 0}}}, \
    {{{COURSE_TILE_S*0, COURSE_TILE_S*((y)+1), 0}, 0, {0, 0}, {C_##c##1, 0}}}
static const Vtx vtx_course_tile[] =
{
    VTX(0, A),
    VTX(2, A),
    VTX(4, A),
    VTX(6, A),
    VTX(8, A),
    VTX(1, A),
    VTX(3, A),
    VTX(5, A),
    VTX(7, A),
    VTX(0, B),
    VTX(2, B),
    VTX(4, B),
    VTX(6, B),
    VTX(8, B),
    VTX(1, B),
    VTX(3, B),
    VTX(5, B),
    VTX(7, B),
};
#undef VTX

static const Gfx gfx_course_tile_4[] =
{
    gsSP2Triangles(15, 14, 13,  0, 15, 13, 12,  0),
    gsSP2Triangles(11, 10,  9,  0, 11,  9,  8,  0),
    gsSP2Triangles( 7,  6,  5,  0,  7,  5,  4,  0),
    gsSP2Triangles( 3,  2,  1,  0,  3,  1,  0,  0),
    gsSPEndDisplayList(),
};
#define gfx_course_tile_1 &gfx_course_tile_4[6]

static const Gfx gfx_course_tile_al[] =
{
    gsSPVertex(&vtx_course_tile[0], 16,  0),
    gsSPDisplayList(gfx_course_tile_4),
    gsSPVertex(&vtx_course_tile[16],  4,  0),
    gsSPBranchList(gfx_course_tile_1),
};

static const Gfx gfx_course_tile_ar[] =
{
    gsSPVertex(&vtx_course_tile[20], 16,  0),
    gsSPBranchList(gfx_course_tile_4),
};

static const Gfx gfx_course_tile_bl[] =
{
    gsSPVertex(&vtx_course_tile[36], 16,  0),
    gsSPDisplayList(gfx_course_tile_4),
    gsSPVertex(&vtx_course_tile[52],  4,  0),
    gsSPBranchList(gfx_course_tile_1),
};

static const Gfx gfx_course_tile_br[] =
{
    gsSPVertex(&vtx_course_tile[56], 16,  0),
    gsSPBranchList(gfx_course_tile_4),
};

static const u16 texture_course_font_zero[] =
{
#include "texture/course/font/zero.h"
};

static const u16 texture_course_font_one[] =
{
#include "texture/course/font/one.h"
};

static const u16 texture_course_font_two[] =
{
#include "texture/course/font/two.h"
};

static const u16 texture_course_font_three[] =
{
#include "texture/course/font/three.h"
};

static const u16 texture_course_font_four[] =
{
#include "texture/course/font/four.h"
};

static const u16 texture_course_font_five[] =
{
#include "texture/course/font/five.h"
};

static const u16 texture_course_font_six[] =
{
#include "texture/course/font/six.h"
};

static const u16 texture_course_font_seven[] =
{
#include "texture/course/font/seven.h"
};

static const u16 texture_course_font_eight[] =
{
#include "texture/course/font/eight.h"
};

static const u16 texture_course_font_nine[] =
{
#include "texture/course/font/nine.h"
};

static const u16 texture_course_font_a[] =
{
#include "texture/course/font/a.h"
};

static const u16 texture_course_font_c[] =
{
#include "texture/course/font/c.h"
};

static const u16 texture_course_font_d[] =
{
#include "texture/course/font/d.h"
};

static const u16 texture_course_font_e[] =
{
#include "texture/course/font/e.h"
};

static const u16 texture_course_font_g[] =
{
#include "texture/course/font/g.h"
};

static const u16 texture_course_font_h[] =
{
#include "texture/course/font/h.h"
};

static const u16 texture_course_font_i[] =
{
#include "texture/course/font/i.h"
};

static const u16 texture_course_font_k[] =
{
#include "texture/course/font/k.h"
};

static const u16 texture_course_font_l[] =
{
#include "texture/course/font/l.h"
};

static const u16 texture_course_font_n[] =
{
#include "texture/course/font/n.h"
};

static const u16 texture_course_font_o[] =
{
#include "texture/course/font/o.h"
};

static const u16 texture_course_font_p[] =
{
#include "texture/course/font/p.h"
};

static const u16 texture_course_font_r[] =
{
#include "texture/course/font/r.h"
};

static const u16 texture_course_font_t[] =
{
#include "texture/course/font/t.h"
};

static const u16 texture_course_font_y[] =
{
#include "texture/course/font/y.h"
};

static const u16 texture_course_font_exclaim[] =
{
#include "texture/course/font/exclaim.h"
};

static const u16 texture_course_font_colon[] =
{
#include "texture/course/font/colon.h"
};

const Gfx gfx_course_start[] =
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

const Gfx gfx_course_end[] =
{
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

const Gfx gfx_course_font_start[] =
{
    gsDPPipeSync(),
    gsDPSetTextureBlock2N(
        G_IM_FMT_RGBA, G_IM_SIZ_16b, COURSE_FONT_W, COURSE_FONT_H, 0,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    ),
    gsSPBranchList(gfx_course_start),
};

const Gfx gfx_course_nodecal[] =
{
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

const Gfx *const gfx_course_tile[] =
{
    gfx_course_tile_al,
    gfx_course_tile_ar,
    gfx_course_tile_br,
    gfx_course_tile_bl,
};

const u16 *const texture_course_font[] =
{
    texture_course_font_zero,
    texture_course_font_one,
    texture_course_font_two,
    texture_course_font_three,
    texture_course_font_four,
    texture_course_font_five,
    texture_course_font_six,
    texture_course_font_seven,
    texture_course_font_eight,
    texture_course_font_nine,
    texture_course_font_a,
    NULL,
    texture_course_font_c,
    texture_course_font_d,
    texture_course_font_e,
    NULL,
    texture_course_font_g,
    texture_course_font_h,
    texture_course_font_i,
    NULL,
    texture_course_font_k,
    texture_course_font_l,
    NULL,
    texture_course_font_n,
    texture_course_font_o,
    texture_course_font_p,
    NULL,
    texture_course_font_r,
    NULL,
    texture_course_font_t,
    NULL,
    NULL,
    NULL,
    NULL,
    texture_course_font_y,
    NULL,
    texture_course_font_exclaim,
    texture_course_font_colon,
};

#else

#endif
