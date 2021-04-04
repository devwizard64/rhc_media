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

.globl s_menu
s_menu:
    s_stage_init()
    s_read_szp(0x07, menu)
    s_read_szp(0x0B, course)
    s_compile_start()
        s_world_start(1, g_menu)
        s_world_end()
    s_compile_end()
    s_world_init(1)
    s_music_play(SEQ_TITLE)
    s_wipe(0x00, 16, 0xFF, 0xFF, 0xFF)
    s_sleep(16)
    s_update(course_menu, 0)
    s_write(STAGE)
    s_wipe(0x01, 16, 0xFF, 0xFF, 0xFF)
    s_sleep(16)
    s_stage_destroy()
    s_sleep(2)
    s_sjump(0x15, game)
