/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#include <ultra64.h>
#include <sm64.h>

#include "course.h"

#define MOTION_DIVE             0x00
#define MOTION_RUNFAST          0x01
#define MOTION_SWIM             0x02
#define MOTION_CHASE            0x03
#define MOTION_RUN              0x04
#define MOTION_DIVE2            0x05
#define MOTION_STANDUP          0x06
#define MOTION_IDLE             0x07
#define MOTION_STANDUP2         0x08
#define MOTION_WALK             0x09
#define MOTION_STOP             0x0A
#define MOTION_CONTINUE         0x0B
#define MOTION_JUMP             0x0C
#define MOTION_LAND             0x0D

#ifndef _SCRIPT

static void opponent_coin(const uintptr_t *script, uint count)
{
    while (true)
    {
        f32 dist;
        struct object_t *object = object_find_distance(script, &dist);
        if (dist > 250)
        {
            break;
        }
        object->flag = 0;
        object_ptr->o_opponent_coin += count;
    }
}

void opponent_update(void)
{
    object_map();
    object_blink(&object_ptr->mem[0x22].s32, 10, 15, 3);
    switch (object_ptr->o_state)
    {
        case 0:
        {
            object_motion(MOTION_IDLE);
            break;
        }
        case 1:
        {
            s16 *path = object_ptr->o_opponent_path;
            if (path != NULL && *path == 0x7FFF)
            {
                path = object_ptr->o_opponent_path = NULL;
            }
            if (path != NULL)
            {
                f32 dx = path[0] - object_ptr->o_pos_x;
                f32 dy = path[1] - object_ptr->o_pos_y;
                f32 dz = path[2] - object_ptr->o_pos_z;
                f32 dh = sqrtf(dx*dx + dz*dz);
                if (dh < 64)
                {
                    object_ptr->o_opponent_path = path+3;
                }
                object_ptr->o_path_rx = atan2(dh, -dy);
                object_ptr->o_path_ry = atan2(dz, dx);
            }
            else
            {
                object_ptr->o_path_rx = 0;
                object_ptr->o_path_ry = object_ptr->o_rot_y;
            }
            switch (object_ptr->o_mode)
            {
                case 0:
                {
                    object_move_vel_f(20, 1.5F);
                    if (object_motion_end(MOTION_CONTINUE))
                    {
                        object_ptr->o_mode++;
                    }
                    break;
                }
                case 1:
                {
                    f32 x = sin(object_ptr->o_path_rx);
                    object_turn_ry(object_ptr->o_path_ry, 600);
                    object_move_vel_f(36 * (1+x), 0.75F);
                    object_motion_vel(MOTION_WALK, 0.1F*object_ptr->o_vel_f);
                    object_motion_sfx_foot(2, 17, 0x50342081);
                    if (object_ptr->o_path_rx < -0x1400)
                    {
                        object_motion(MOTION_JUMP);
                        object_ptr->o_vel_y = 40 * (1-x);
                        object_ptr->o_move_flag = 0;
                        object_ptr->o_mode++;
                    }
                    break;
                }
                case 2:
                {
                    if (object_ptr->o_move_flag & 0x00000003)
                    {
                        if (object_motion_end(MOTION_LAND))
                        {
                            object_ptr->o_mode--;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 2:
        {
            object_move_vel_f(0, 2);
            object_motion_vel(MOTION_WALK, 0.1F*object_ptr->o_vel_f);
            object_motion_sfx_foot(2, 17, 0x50342081);
            if (object_ptr->o_vel_f < 1)
            {
                object_ptr->o_state = 0;
            }
            break;
        }
    }
    object_move(-78);
    object_turn_gfx_ry(object_ptr->o_rot_y, 0x0600);
    opponent_coin(o_coin,    1);
    opponent_coin(o_redcoin, 3);
    if (main_debug_mem)
    {
        print_int(180, 160-18*0, "x %d", object_ptr->o_pos_x);
        print_int(180, 160-18*1, "y %d", object_ptr->o_pos_y);
        print_int(180, 160-18*2, "z %d", object_ptr->o_pos_z);
    }
}

#else

#define O_M_COIN                0x1C

.globl o_opponent
o_opponent:
    o_init(OBJECTB)
    o_setflag(FLAG, 0x0001)
    o_seti(COIN, 0)
    o_move(50, -400, 0, 0, 1000, 200, 0, 0)
    o_scale(300)
    o_ptr(MOTION, 0x06011364)
    o_motion(MOTION_IDLE)
    o_while()
        o_callback(opponent_update)
    o_wend()

#endif
