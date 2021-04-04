/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#ifndef _COURSE_H_
#define _COURSE_H_

#include <ultra64.h>
#include <sm64.h>

#ifndef __ASSEMBLER__

#define COURSE_LEN              2

#define COURSE_TILE_S           24

#define COURSE_FONT_W           16
#define COURSE_FONT_H           22

#define o_opponent_path         mem[0x1B].ptr
#define o_opponent_coin         mem[0x1C].u32

extern const Gfx gfx_course_start[];
extern const Gfx gfx_course_end[];
extern const Gfx gfx_course_nodecal[];

extern s32  course_menu(s16, s32);
extern s32  course_end_init(s16, s32);
extern s32  course_end_update(s16, s32);
extern s32  course_message(s16, s32);
extern uint course_lock(void);
extern uint course_lose(void);
extern struct object_t *course_object(void);
extern void course_out(void);
extern void course_latch(void);
extern s32  course_init(s16, s32);
extern s32  course_update(s16, s32);
extern void course_hud(void);

#endif

#endif /* _COURSE_H_ */
