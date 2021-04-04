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

const u16 texture_stage_course1_bg[] =
{
#include "texture/stage/course1/bg.h"
};

const u16 texture_stage_course1_wa_0[] =
{
#include "texture/stage/course1/wa_0.h"
};

const u16 texture_stage_course1_wa_1[] =
{
#include "texture/stage/course1/wa_1.h"
};

const u16 texture_stage_course1_wa_2[] =
{
#include "texture/stage/course1/wa_2.h"
};

const u16 texture_stage_course1_wa_3[] =
{
#include "texture/stage/course1/wa_3.h"
};

const u16 texture_stage_course1_wa_4[] =
{
#include "texture/stage/course1/wa_4.h"
};

const u16 texture_stage_course1_wa_5[] =
{
#include "texture/stage/course1/wa_5.h"
};

const u16 texture_stage_course1_wb_0[] =
{
#include "texture/stage/course1/wb_0.h"
};

const u16 texture_stage_course1_wb_1[] =
{
#include "texture/stage/course1/wb_1.h"
};

const u16 texture_stage_course1_wb_2[] =
{
#include "texture/stage/course1/wb_2.h"
};

const u16 texture_stage_course1_wb_3[] =
{
#include "texture/stage/course1/wb_3.h"
};

const u16 texture_stage_course1_wb_4[] =
{
#include "texture/stage/course1/wb_4.h"
};

const u16 texture_stage_course1_wb_5[] =
{
#include "texture/stage/course1/wb_5.h"
};

#define BOUND(xl, xh, yl, yh, zl, zh)   0, xl, zl, xh, zh, yh,
const s16 map_stage_course1[] =
{
#include "shape/stage/course1/m_w1_vtx.h"
    0x0015,
#include "shape/stage/course1/m_w1_w1.h"
#include "shape/stage/course1/m_w2_vtx.h"
    0x0015,
#include "shape/stage/course1/m_w2_w2.h"
    M_BREAK,
    M_WATER, 2,
#include "shape/stage/course1/b_water1.h"
#include "shape/stage/course1/b_water2.h"
    M_END,
};
#undef BOUND

#define COUNT(count)

#define P_COIN(x, y, z)         S_O_COIN, x, y, z, 0,
#define P_REDCOIN(x, y, z)      S_O_REDCOIN, x, y, z, 0,
#define P_CORKBOX(x, y, z)      S_O_CORKBOX, x, y, z, 0,

const s16 obj_stage_course1[] =
{
#define POINT   P_COIN
#include "shape/stage/course1/p_coin1.h"
#include "shape/stage/course1/p_coin2.h"
#undef POINT
#define POINT   P_REDCOIN
#include "shape/stage/course1/p_mcoin2.h"
#undef POINT
#define POINT   P_CORKBOX
#include "shape/stage/course1/p_box1.h"
#include "shape/stage/course1/p_box2.h"
#undef POINT
    S_O_END,
};

#define POINT(x, y, z)          x, y, z,

const s16 path_stage_course1_1[] =
{
    COUNT(23)
    POINT(-2234, -4300, -32)
    POINT(-1946, -4198, -32)
    POINT(-1850, -4198, -32)
    POINT(-1562, -4300, -32)
    POINT(-1178, -4300, -32)
    POINT(-1002, -4215, -32)
    POINT(-714, -4113, -32)
    POINT(-602, -4113, -32)
    POINT(-394, -3952, -32)
    POINT(-106, -4215, -32)
    POINT(158, -4113, -32)
    POINT(286, -4113, -32)
    POINT(574, -4215, -32)
    POINT(1110, -4215, -32)
    POINT(1238, -3934, -32)
    POINT(2078, -4215, -32)
    POINT(2078, -3934, -32)
    POINT(2274, -4113, -32)
    POINT(2954, -4113, -32)
    POINT(3434, -4317, -32)
    POINT(3854, -4062, -32)
    POINT(4298, -4317, -32)
    POINT(4586, -4206, -32)
    0x7FFF,
};

const s16 path_stage_course1_2[] =
{
    COUNT(25)
    POINT(-4204, -110, -32)
    POINT(-4060, 170, -32)
    POINT(-3672, -110, -32)
    POINT(-3288, -212, -32)
    POINT(-2984, -212, -32)
    POINT(-2816, 272, -32)
    POINT(-2304, -212, -32)
    POINT(-1696, -212, -32)
    POINT(-1568, 51, -32)
    POINT(-1276, -212, -32)
    POINT(-512, -212, -32)
    POINT(-416, -110, -32)
    POINT(-120, -110, -32)
    POINT(72, 110, -32)
    POINT(456, 110, -32)
    POINT(640, 212, -32)
    POINT(928, 212, -32)
    POINT(1224, 212, -32)
    POINT(1416, 212, -32)
    POINT(1608, 212, -32)
    POINT(1896, 212, -32)
    POINT(2184, 212, -32)
    POINT(4068, -212, -32)
    POINT(4196, 68, -32)
    POINT(5752, -212, -32)
    0x7FFF,
};

#else

const uintptr_t g_stage_course1[] =
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
