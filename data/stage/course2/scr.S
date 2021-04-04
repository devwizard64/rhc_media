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
#include "bgmap.h"

.globl s_stage_course2
s_stage_course2:
    s_stage_init()
    s_read_szp(0x07, stage_course2)
    s_read_szp(0x0B, course)
    s_read_scr(0x1A, course)
    s_read_szp(0x06, object_b2)
    s_read_scr(0x0D, object_b2)
    s_read_szp(0x08, object_c0)
    s_read_scr(0x0F, object_c0)
    s_compile_start()
        s_mario()
        s_call(s_object_c0)
        s_call(s_object_b2)
        s_world_start(1, g_stage_course2)
            s_world_map(map_stage_course2)
            s_world_obj(obj_stage_course2)
            s_world_env(0x0000)
            s_world_music(0x0000, SEQ_COURSE2)
        s_world_end()
    s_compile_end()
    s_mario_init(1, 90, BGMAP_O(2, 1)+C2_L1 + 4*60, -289 - 4096, 32)
    s_callback(game_main, 0)
    s_callback(bgmap_init, 1)
    s_update(course_update, 1)
    s_stage_destroy()
    s_freeze(1)
    s_sreturn()
