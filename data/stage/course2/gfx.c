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

#ifndef _SCRIPT

const u16 texture_stage_course2_bg[] =
{
#include "texture/stage/course2/bg.h"
};

const Gfx gfx_stage_course2[] =
{
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00010001U),
    gsDPFillRectangle(0,   8, 320-1,  24-1),
    gsDPFillRectangle(0, 216, 320-1, 232-1),
    gsDPPipeSync(),
    gsDPSetScissorFrac(G_SC_NON_INTERLACE, 0 << 2, 24 << 2, 320 << 2, 216 << 2),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

const s16 map_stage_course2[] =
{
#include "shape/stage/course2/m_w1_vtx.h"
    0x0015,
#include "shape/stage/course2/m_w1_w1.h"
#include "shape/stage/course2/m_w2_vtx.h"
    0x0015,
#include "shape/stage/course2/m_w2_w2.h"
#include "shape/stage/course2/m_w3_vtx.h"
    0x0015,
#include "shape/stage/course2/m_w3_w3.h"
    M_BREAK,
    M_END,
};

#define COUNT(count)

#define P_COIN(x, y, z)         S_O_COIN, x, y, z, 0,
#define P_REDCOIN(x, y, z)      S_O_REDCOIN, x, y, z, 0,

const s16 obj_stage_course2[] =
{
#define POINT   P_COIN
#include "shape/stage/course2/p_coin1.h"
#include "shape/stage/course2/p_coin2.h"
#include "shape/stage/course2/p_coin3.h"
#undef POINT
#define POINT   P_REDCOIN
#include "shape/stage/course2/p_mcoin1.h"
#include "shape/stage/course2/p_mcoin2.h"
#include "shape/stage/course2/p_mcoin3.h"
#undef POINT
    S_O_END,
};

#define POINT(x, y, z)          x, y, z,

const s16 path_stage_course2_1[] =
{
    COUNT(23)
    POINT(-4098, -4385, -32)
    POINT(-2120, -4385, -32)
    POINT(-1832, -4283, -32)
    POINT(-1544, -4283, -32)
    POINT(-1256, -4385, -32)
    POINT(-872, -4385, -32)
    POINT(-584, -4283, -32)
    POINT(-296, -4283, -32)
    POINT(-8, -4130, -32)
    POINT(248, -4385, -32)
    POINT(800, -4385, -32)
    POINT(1336, -3739, -32)
    POINT(1464, -3739, -32)
    POINT(1624, -4385, -32)
    POINT(2200, -4385, -32)
    POINT(2456, -3841, -32)
    POINT(2680, -4385, -32)
    POINT(3160, -4385, -32)
    POINT(3256, -4283, -32)
    POINT(3448, -4181, -32)
    POINT(3736, -4181, -32)
    POINT(3928, -4283, -32)
    POINT(4024, -4385, -32)
    0x7FFF,
};

const s16 path_stage_course2_2[] =
{
    COUNT(23)
    POINT(-3888, -289, -32)
    POINT(-3600, -187, -32)
    POINT(-3408, -85, -32)
    POINT(-3120, 17, -32)
    POINT(-2928, 17, -32)
    POINT(-2736, 459, -32)
    POINT(-2544, 17, -32)
    POINT(-1584, 17, -32)
    POINT(-1168, 561, -32)
    POINT(-912, 561, -32)
    POINT(-432, 17, -32)
    POINT(432, 561, -32)
    POINT(720, -187, -32)
    POINT(912, -85, -32)
    POINT(1104, 17, -32)
    POINT(1200, 561, -32)
    POINT(1392, -298, -32)
    POINT(2352, -298, -32)
    POINT(2448, -196, -32)
    POINT(2544, 348, -32)
    POINT(2800, -298, -32)
    POINT(3024, 348, -32)
    POINT(4558, -298, -32)
    0x7FFF,
};

const s16 path_stage_course2_3[] =
{
    COUNT(33)
    POINT(-4520, 3900, -32)
    POINT(-4392, 4444, -32)
    POINT(-3752, 3798, -32)
    POINT(-3560, 3900, -32)
    POINT(-3272, 3900, -32)
    POINT(-2984, 3798, -32)
    POINT(-2408, 3798, -32)
    POINT(-2088, 4342, -32)
    POINT(-1832, 3798, -32)
    POINT(-1736, 3798, -32)
    POINT(-1448, 3900, -32)
    POINT(-1352, 3900, -32)
    POINT(-1256, 4002, -32)
    POINT(-872, 3798, -32)
    POINT(-584, 3798, -32)
    POINT(-392, 3900, -32)
    POINT(-104, 3900, -32)
    POINT(88, 3798, -32)
    POINT(376, 3798, -32)
    POINT(472, 3900, -32)
    POINT(664, 4002, -32)
    POINT(952, 4002, -32)
    POINT(1145, 3900, -32)
    POINT(1385, 4444, -32)
    POINT(1529, 3807, -32)
    POINT(1721, 3909, -32)
    POINT(1817, 4011, -32)
    POINT(2009, 4113, -32)
    POINT(2297, 4113, -32)
    POINT(2489, 4011, -32)
    POINT(2585, 3909, -32)
    POINT(2777, 3807, -32)
    POINT(5096, 3807, -32)
    0x7FFF,
};

#else

const uintptr_t g_stage_course2[] =
{
    g_world(160, 120, 160, 120, 10),
    g_start(),
        g_layer(true),
        g_start(),
            g_perspective(45, 100, 30000, camera_g_persp),
            g_start(),
                g_bgmap(),
                g_start(),
                    g_gfx(XLU_DECAL, gfx_course_nodecal),
                    g_object(),
                g_end(),
            g_end(),
        g_end(),
    g_end(),
    g_exit(),
};

#endif
