/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#ifndef _BGMAP_H_
#define _BGMAP_H_

#include <ultra64.h>
#include <gbi_ext.h>
#include <sm64.h>

#define BGMAP_L 640

#define C1_L1   -9936
#define C1_R1   292
#define C1_L2   -236
#define C1_R2   9220

#define C2_L1   -14592
#define C2_R1   -4048
#define C2_L2   -5296
#define C2_R2   4976
#define C2_L3   4400
#define C2_R3   14592

#define BGMAP_O(i, n)           ((C##i##_L##n+C##i##_R##n)/-2)
#define BGMAP_T(i, n)           (BGMAP_L+C##i##_L1+BGMAP_O(i, n))

#ifndef __ASSEMBLER__

#define g_bgmap()               g_camera(0x0E, 0, 0, 0, 0, 0, 0, bgmap_g_main)

extern s32 bgmap_init(s16, s32);
extern Gfx *bgmap_g_main(int, struct gc_t *, void *);

#endif

#endif /* _BGMAP_H_ */
