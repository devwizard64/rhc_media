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

.globl s_stage_end
s_stage_end:
    s_stage_init()
    s_read_szp(0x07, stage_end)
    s_read_szp(0x0B, course)
    s_compile_start()
        s_world_start(1, g_stage_end_1)
        s_world_end()
        s_world_start(2, g_stage_end_2)
        s_world_end()
    s_compile_end()
    s_world_init(1)
    s_music_play(SEQ_DRUMROLL)
    s_wipe(0x00, 16, 0xFF, 0xFF, 0xFF)
    s_callback(course_end_init, 0)
    s_update(course_end_update, 0)
    s_wipe(0x01, 16, 0xFF, 0xFF, 0xFF)
    s_sleep(16)
    s_cjump(NE, 1, lose)
    s_music_play(SEQ_WIN)
    s_jump(end)
lose:
    s_music_play(SEQ_LOSE)
end:
    s_wipe(0x00, 16, 0xFF, 0xFF, 0xFF)
    s_update(course_message, 0)
    s_wipe(0x01, 16, 0xFF, 0xFF, 0xFF)
    s_sleep(16)
    s_world_destroy(1)
    s_world_init(2)
    s_music_play(SEQ_LOOP1)
    s_wipe(0x00, 16, 0xFF, 0xFF, 0xFF)
    s_update(course_message, 1)
    s_wipe(0x01, 16, 0xFF, 0xFF, 0xFF)
    s_sleep(16)
    s_set(-9)
    s_stage_destroy()
    s_freeze(1)
    s_sreturn()
