/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#include <ultra64.h>
#include <gbi_ext.h>
#include <sm64.h>

#include "seq.h"

.globl s_stage_course3
s_stage_course3:
    s_stage_init()
    s_read_szp(0x07, stage_course3)
    s_read_tex(0x09, texture_02)
    s_read_szp(0x0A, background_00)
    s_read_szp(0x0B, course)
    s_read_scr(0x1A, course)
    s_read_szp(0x05, object_a2)
    s_read_scr(0x0C, object_a2)
    s_read_szp(0x06, object_b2)
    s_read_scr(0x0D, object_b2)
    s_read_szp(0x08, object_c0)
    s_read_scr(0x0F, object_c0)
    s_compile_start()
        s_mario()
        s_call(s_object_c0)
        s_call(s_object_a2)
        s_call(s_object_b2)
        s_g_scr(0x17, 0x16000FE8)
        s_g_scr(0x36, g_0E000440)
        s_g_scr(0x37, g_0E000458)
        s_world_start(1, g_stage_course3)
            s_object_all(0x36,  1456,   768,   446,    0,  326,    0, 0x00, 0x00, 0, 0x13004868)
            s_object_all(0x37, -2303,   717,  1024,    0,   45,    0, 0x00, 0x03, 0, 0x13004B1C)
            s_object_all(0x00, -2050,     0, -3069,    0,   25,    0, 0x00, 0x00, 0, 0x130025E0)
            s_object_all(0xCF, -2283,     0, -3682,    0,   27,    0, 0x00, 0x00, 0, 0x13001478)
            s_object_all(0xCA,  1612,   300,  4611,    0,    0,    0, 0x00, 0x28, 0, 0x13001B70)
            s_object_all(0x00,  1535,  3840, -5561,    0,    0,    0, 0x00, 0x00, 0, 0x13003AA4)
            s_object_all(0x00,   524,  2825, -5400,    0,    0,    0, 0x00, 0x02, 0, 0x13003AA4)
            s_object_all(0xB4,  -993,   886, -3565,    0,    0,    0, 0x00, 0x00, 0, 0x13003A08)
            s_object_all(0xB4,  -785,   886, -4301,    0,    0,    0, 0x00, 0x00, 0, 0x13003A08)
            s_object_all(0xB4,   -93,   886, -3414,    0,    0,    0, 0x00, 0x00, 0, 0x13003A08)
            s_object_all(0xC3, -5723,   140,  6017,    0,    0,    0, 0x00, 0x00, 0, 0x13003228)
            s_object_all(0xC3, -6250,     0,  6680,    0,    0,    0, 0x00, 0x03, 0, 0x130031DC)
            s_object_all(0xC9, -5694,   128,  5600,    0,  180,    0, 0x00, 0x00, 0, 0x13003274)
            s_object_all(0x00,  3304,  4242, -4603,    0,    0,    0, 0x00, 0x00, 0, 0x130045D0)
            s_object_all(0x68,  3400,   770,  6500,    0,    0,    0, 0x00, 0x01, 0, 0x13004580)
            /*
            s_object_all(0x00, -6000,  1000,  2400,    0,    0,    0, 0x03, 0x00, 0, 0x13003E8C)
            s_object_all(0x00, -6600,  1000,  1250,    0,    0,    0, 0x04, 0x04, 0, 0x13003EFC)
            s_object_all(0x7A,  1550,  1200,   300,    0,    0,    0, 0x05, 0x00, 0, 0x13003E3C)
            */
            s_object_all(0x00,   583,  2683, -5387,    0, -154,    0, 0x00, 0x0B, 0, 0x1300075C)
            s_object_all(0x00,  1680,  3835, -5523,    0, -153,    0, 0x00, 0x0C, 0, 0x1300075C)
            s_object_all(0x00, -6612,  1024, -3351,    0,  107,    0, 0x00, 0x0D, 0, 0x1300075C)
            s_object_all(0x00,  1980,   768,  6618,    0, -151,    0, 0x00, 0x0E, 0, 0x1300075C)
            s_link(0x0B, 0x03, 0x01, 0x0C)
            s_link(0x0C, 0x03, 0x01, 0x0B)
            s_link(0x0D, 0x03, 0x01, 0x0E)
            s_link(0x0E, 0x03, 0x01, 0x0D)
            s_world_map(0x0700E958)
            s_world_obj(0x0701104C)
            s_world_music(0, SEQ_COURSE3)
            s_world_env(0)
        s_world_end()
    s_compile_end()
    s_mario_init(1, 135, -6558, 0, 6464)
    s_callback(game_main, 0)
    s_callback(course_init, 2)
    s_update(course_update, 1)
    s_stage_destroy()
    s_freeze(1)
    s_sreturn()
