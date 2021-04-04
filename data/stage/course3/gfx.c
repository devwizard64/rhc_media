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

#else

const uintptr_t g_0E000440[] =
{
    0x200003E8,
    g_start(),
        g_gfx(SPRITE, 0x0700E458),
    g_end(),
    g_exit(),
};

const uintptr_t g_0E000458[] =
{
    0x200004B0,
    g_start(),
        g_gfx(OPA_SURF, 0x0700E768),
    g_end(),
    g_exit(),
};

const uintptr_t g_stage_course3[] =
{
    g_world(160, 120, 160, 120, 10),
    g_start(),
        g_layer(false),
        g_start(),
            g_ortho(100),
            g_start(),
                g_background(0, 0x802763D4),
            g_end(),
        g_end(),
        g_layer(true),
        g_start(),
            g_perspective(45, 100, 30000, camera_g_persp),
            g_start(),
                g_camera(1, 0, 2000, 6000, 3072, 0, -4608, camera_g_camera),
                g_start(),
                    g_gfx(OPA_SURF,  0x07004390),
                    g_gfx(OPA_SURF,  0x07009D80),
                    g_gfx(XLU_DECAL, 0x0700A470),
                    g_gfx(SPRITE,    0x0700A920),
                    g_gfx(OPA_SURF,  0x0700DD18),
                    g_gfx(OPA_SURF,  0x0700E338),
                    g_object(),
                    g_callback(0, 0x802761D0),
                g_end(),
            g_end(),
        g_end(),
        g_layer(false),
        g_start(),
            g_callback(0, 0x802CD1E8),
        g_end(),
    g_end(),
    g_exit(),
};

#endif
