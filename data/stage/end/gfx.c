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

static const u8 texture_stage_end_logo[] =
{
#include "texture/stage/end/logo.h"
};

#define LOGO_W      256
#define LOGO_H      16
#define LOGO_X      96
#define LOGO_Y      56

#define gsLogoTile(n)                                       \
    gsDPSetTextureImage(                                    \
        G_IM_FMT_I, G_IM_SIZ_16b, 1,                        \
        &texture_stage_end_logo[LOGO_W*LOGO_H*(n)]          \
    ),                                                      \
    gsDPLoadTextureBlock2(G_IM_SIZ_8b, LOGO_W, LOGO_H),     \
    gsSPTextureRectangle(                                   \
        4*LOGO_X + 2*LOGO_W*((0)+0),                        \
        4*LOGO_Y + 2*LOGO_H*((n)+0),                        \
        4*LOGO_X + 2*LOGO_W*((0)+1),                        \
        4*LOGO_Y + 2*LOGO_H*((n)+1),                        \
        G_TX_RENDERTILE, 0, 0, 0x0800, 0x0800               \
    ),                                                      \
    gsDPPipeSync()

const Gfx gfx_end_logo[] =
{
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureBlock2N(
        G_IM_FMT_I, G_IM_SIZ_8b, LOGO_W, LOGO_H, 0,
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
    gsLogoTile(8),
    gsLogoTile(9),
    gsLogoTile(10),
    gsLogoTile(11),
    gsLogoTile(12),
    gsLogoTile(13),
    gsLogoTile(14),
    gsLogoTile(15),
    gsSPEndDisplayList(),
};

#else

extern const Gfx gfx_end_logo[];

const uintptr_t g_stage_end_1[] =
{
    g_world(160, 120, 160, 120, 0),
    g_start(),
        g_layer(false),
        g_start(),
            g_ortho(100),
            g_start(),
                g_background(0xF7BD, NULL),
            g_end(),
        g_end(),
    g_end(),
    g_exit(),
};

const uintptr_t g_stage_end_2[] =
{
    g_world(160, 120, 160, 120, 0),
    g_start(),
        g_layer(false),
        g_start(),
            g_ortho(100),
            g_start(),
                g_background(0x0001, NULL),
                g_gfx(BACKGROUND, gfx_course_start),
                g_gfx(BACKGROUND, gfx_end_logo),
                g_gfx(BACKGROUND, gfx_course_end),
            g_end(),
        g_end(),
    g_end(),
    g_exit(),
};

#endif
