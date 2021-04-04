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

static const u16 texture_menu_logo[] =
{
#include "texture/menu/logo.h"
};

#define LOGO_W      32
#define LOGO_H      64
#define LOGO_X      32
#define LOGO_Y      64

#define gsLogoTile(n)                                       \
    gsDPSetTextureImage(                                    \
        G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,                     \
        &texture_menu_logo[LOGO_H*LOGO_W*(n)]               \
    ),                                                      \
    gsDPLoadTextureBlock2(G_IM_SIZ_16b, LOGO_H, LOGO_W),    \
    gsSPTextureRectangleFlip(                               \
        (LOGO_X+LOGO_W*((n)+0)) << 2,                       \
        (LOGO_Y+LOGO_H*((0)+0)) << 2,                       \
        (LOGO_X+LOGO_W*((n)+1)) << 2,                       \
        (LOGO_Y+LOGO_H*((0)+1)) << 2,                       \
        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400               \
    ),                                                      \
    gsDPPipeSync()

const Gfx gfx_menu_logo[] =
{
    gsDPSetTextureBlock2N(
        G_IM_FMT_RGBA, G_IM_SIZ_16b, LOGO_H, LOGO_W, 0,
        G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
    ),
    gsLogoTile(0),
    gsLogoTile(1),
    gsLogoTile(2),
    gsLogoTile(3),
    gsLogoTile(4),
    gsLogoTile(5),
    gsLogoTile(6),
    gsLogoTile(7),
    gsSPEndDisplayList(),
};

#define gdSPDefLights1_AD(a, d, x, y, z)    gdSPDefLights1(a, d, x, y, z)
#define R(c)    ((uint)(u8)((c) >> 16))
#define G(c)    ((uint)(u8)((c) >>  8))
#define B(c)    ((uint)(u8)((c) >>  0))
#define A(c)    (R(c)/2), (G(c)/2), (B(c)/2)
#define D(c)    (R(c)/1), (G(c)/1), (B(c)/1)
#define L(c)    gdSPDefLights1_AD(A(c), D(c), 0, 80, 40)
static const Lights1 light_b = L(0x5a71e4);
static const Lights1 light_g = L(0x00e700);
static const Lights1 light_y = L(0xf2f236);
static const Lights1 light_r = L(0xea2b2b);

#include "shape/menu/g_m_vtx.h"
#include "shape/menu/g_a_vtx.h"
#include "shape/menu/g_r_vtx.h"
#include "shape/menu/g_i_vtx.h"
#include "shape/menu/g_o_vtx.h"

const Gfx gfx_menu[] =
{
    gsSPSetLights1N(light_b),
#include "shape/menu/g_m_None.h"
    gsSPSetLights1N(light_g),
#include "shape/menu/g_a_None.h"
#include "shape/menu/g_o_None.h"
    gsSPSetLights1N(light_y),
#include "shape/menu/g_r_None.h"
    gsSPSetLights1N(light_r),
#include "shape/menu/g_i_None.h"
    gsSPEndDisplayList(),
};

#else

extern const Gfx gfx_menu_logo[];
extern const Gfx gfx_menu[];

const uintptr_t g_menu[] =
{
    g_world(160, 120, 160, 120, 0),
    g_start(),
        g_layer(false),
        g_start(),
            g_ortho(100),
            g_start(),
                g_background(0xF7BD, NULL),
                g_gfx(BACKGROUND, gfx_course_start),
                g_gfx(BACKGROUND, gfx_menu_logo),
                g_gfx(BACKGROUND, gfx_course_end),
            g_end(),
        g_end(),
        g_layer(true),
        g_start(),
            g_persp(30, 100, 30000),
            g_start(),
                g_gfx_pos(OPA_SURF, gfx_menu, -64, 768, -5120),
            g_end(),
        g_end(),
    g_end(),
    g_exit(),
};

#endif
