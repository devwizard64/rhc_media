/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#include <ultra64.h>
#include <gbi_ext.h>
#include <sm64.h>

.globl s_main
s_main:
    s_stage_init()
    s_sleep(2)
    s_vi_black(false)
    s_scall(0x14, menu)
    s_jump(s_main)
