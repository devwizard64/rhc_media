;                       rhc_media - Mario no Gourmetrace
;                        Copyright (C) 2020  devwizard
;         This project is licensed under the terms of the GNU General
;         Public License version 2.  See LICENSE for more information.

.create _DST, 0
.include "include/ultra64.asm"
.include "include/sm64.asm"

.definelabel heap_start,                0x80025C00
.definelabel heap_end,                  0x801C1000
.definelabel main3_start,               main_end
.definelabel bgmap_szp,                 main2_start-0x3400

.include "src/header.asm"
.incbin "ultra/ipl3.bin"

.orga seg_main_start
.base main_start
.incbin "src/main.bin"

.org profiler_update
mem_init_main3:
    la      a0, main3_start
    la      a1, seg_main3_start
    la.u    a2, seg_main3_end
    j       mem_dma_read
    la.l    a2, seg_main3_end
.org mem_init_main2
.skip 0x98
    j       mem_init_main3

.org scheduler_init_mem
.skip 0x08
    li      t6, heap_start
    sw      t6, 0x1C(sp)
    li      t7, heap_end
    sw      t7, 0x18(sp)

.org app_init
.skip 0xE8
    la.u    a1, seg_motion_player
.skip 0x08
    la.l    a1, seg_motion_player
.skip 0x30
    la.u    a1, seg_demo
.skip 0x08
    la.l    a1, seg_demo
.skip 0x08
    la.u    a1, scr_main_start
    la.u    a2, scr_main_end
    la.l    a2, scr_main_end
    la.l    a1, scr_main_start
.skip 0x0C
    la.u    a1, szp_main_start
    la.u    a2, szp_main_end
    la.l    a2, szp_main_end
    la.l    a1, szp_main_start

.org 0x80265244
.skip 0x78
    li      at, 0x3FA00000 ; 1.25F
    mtc1    at, f4
    lwc1    f6, 0x0018(sp)
    mul.s   f6, f4, f6
    b       0x80265244+0xC8
    swc1    f6, 0x0018(sp)
.skip 0x90
    li      at, 0x42570000 ; 1.25F*43
.skip 0x64
    li      at, 0x42700000 ; 1.25F*48
.skip 0x18
    li      at, 0x42700000 ; 1.25F*48

.org 0x802D6B3C
.skip 0x80
    addiu   t8, t7, 16
.skip 0x08
    addiu   t4, t3, 16
.skip 0x98
    li      t7, 0x04000400

.org print_draw
.skip 0x124
    la      t5, gfx_print_start
.skip 0x138
    la      t6, gfx_print_end
.skip 0x1C
    j       course_draw

.org 0x802E2CF0
.skip 0xA8
    addiu   t4, a0, 16
.skip 0x08
    addiu   t9, a1, 16
.skip 0x94
    li      t8, 0x04000400

.org 0x802E2E58
.skip 0x19C
    addiu   t2, a0, 8
.skip 0x08
    addiu   t7, a1, 8
.skip 0x94
    li      t6, 0x04000400

.org 0x802E395C
.skip 0x140
    la      t8, gfx_print_start
.skip 0x54
    la      t4, gfx_print_end

.org 0x802E3B3C
.skip 0x6C
    la      t3, gfx_print_start
.skip 0x154
    la      t7, gfx_print_end

; life
.org 0x802E3744
    jr      ra
    nop
; coin
.org 0x802E37A8
    addiu   sp, sp, -0x0018
    sw      ra, 0x0014(sp)
    la      a2, 0x8033838C
    li      a0, 22
    jal     print
    li      a1, 209
    la      a2, 0x80338390
    li      a0, 22+16
    jal     print
    li      a1, 209
    lh      a3, 0x8033B262
    la      a2, 0x80338394
    li      a0, 22+16+14
    li      a1, 209
    lw      ra, 0x0014(sp)
    j       print_int
    addiu   sp, sp, 0x0018
; star
.org 0x802E380C
    addiu   sp, sp, -0x0018
    sw      ra, 0x0014(sp)
    la      a2, 0x8033838C
    li      a0, 242
    jal     print
    li      a1, 209
    la      a2, 0x80338390
    li      a0, 242+16
    jal     print
    li      a1, 209
    lhu     a3, course_coin
    la      a2, 0x80338394
    li      a0, 242+16+14
    li      a1, 209
    lw      ra, 0x0014(sp)
    j       print_int
    addiu   sp, sp, 0x0018
; camera
.org 0x802E3B3C
    jr      ra
    nop

.org audio_init
.skip 0x208
    la.u    a0, seg_audio_seq
.skip 0x04
    la.l    a0, seg_audio_seq
.skip 0x48
    la.u    a0, seg_audio_seq
.skip 0x04
    la.l    a0, seg_audio_seq
.skip 0x10
    la      a1, seg_audio_seq
.skip 0x14
    la.u    a0, seg_audio_ctl
.skip 0x04
    la.l    a0, seg_audio_ctl
.skip 0x58
    la.u    a0, seg_audio_ctl
.skip 0x04
    la.l    a0, seg_audio_ctl
.skip 0x10
    la      a1, seg_audio_ctl
.skip 0x14
    la.u    a0, seg_audio_ctl
.skip 0x04
    la.l    a0, seg_audio_ctl
.skip 0x3C
    la.u    a0, seg_audio_tbl
.skip 0x04
    la.l    a0, seg_audio_tbl
.skip 0x10
    la      a1, seg_audio_tbl
.skip 0x1C
    la.u    a0, seg_audio_bnk
.skip 0x04
    la.l    a0, seg_audio_bnk

.org main_debug_stage
    .db true
; .org main_debug_mem
;     .db true

.org save_course_table
    .db  1 ;  1
    .db  2 ;  2
    .db  3 ;  3
    .db  0 ;  4
    .db  0 ;  5
    .db  0 ;  6
    .db  0 ;  7
    .db  0 ;  8
    .db  0 ;  9
    .db  0 ; 10
    .db  0 ; 11
    .db  0 ; 12
    .db  0 ; 13
    .db  0 ; 14
    .db  0 ; 15
    .db  0 ; 16
    .db  0 ; 17
    .db  0 ; 18
    .db  0 ; 19
    .db  0 ; 20
    .db  0 ; 21
    .db  0 ; 22
    .db  0 ; 23
    .db  0 ; 24
    .db  0 ; 25
    .db  0 ; 26
    .db  0 ; 27
    .db  0 ; 28
    .db  0 ; 29
    .db  0 ; 30
    .db  0 ; 31
    .db  0 ; 32
    .db  0 ; 33
    .db  0 ; 34
    .db  0 ; 35
    .db  0 ; 36
    .db  0 ; 37
    .db  0 ; 38

.org 0x80332794
.skip 0x05
    .db 3

.orga seg_main2_start
.base main2_start
.incbin "src/main2.bin"

.seg seg_main3_start
.base main3_start
.importobj _BUILD + "/main3.o"
; .notice "main3: " + (bgmap_szp-.)
.seg seg_main3_end

#define SCR(path, name, addr)                           \
    .seg scr_##name##_start ::                          \
    .base addr ::                                       \
    .importobj _BUILD + "/data/" + path + ".o" ::       \
    .seg scr_##name##_end
#define SCR_BIN(path, name)                             \
    .seg scr_##name##_start ::                          \
    .incbin "data/" + path + ".bin" ::                  \
    .seg scr_##name##_end
#define SCR_STAGE(path, name, addr)                     \
    .seg scr_##name##_start ::                          \
    .base addr ::                                       \
    .importobj _BUILD + "/data/" + path + "/scr.o" ::   \
    .importobj _BUILD + "/data/" + path + "/gfx.o" ::   \
    .seg scr_##name##_end
#define SZP(path, name)                                 \
    .seg szp_##name##_start ::                          \
    .include _BUILD + "/data/" + path + ".asm" ::       \
    .incbin  _BUILD + "/data/" + path + ".szp" ::       \
    .seg szp_##name##_end

SCR("scr_main", main, 0x10000000)
SZP("gfx_main", main)

SZP("object/gfx_player", object_player)
SCR_BIN("object/scr_player", object_player)
SZP("object/gfx_a2", object_a2)
SCR_BIN("object/scr_a2", object_a2)
SZP("object/gfx_b2", object_b2)
SCR_BIN("object/scr_b2", object_b2)
SZP("object/gfx_c0", object_c0)
SCR_BIN("object/scr_c0", object_c0)
SZP("object/gfx_entity", object_entity)
SCR_BIN("object/scr_entity", object_entity)
SCR_BIN("object/scr", object)
.definelabel o_coin,                    0x1300091C
.definelabel o_mario,                   0x13002EC0
.definelabel o_redcoin,                 0x13003EAC

SCR_STAGE("menu", menu, 0x14000000)
SZP("menu/gfx", menu)

SCR_BIN("scr_game", game)
.definelabel s_object_c0,               0x15000660
.definelabel s_object_a2,               0x1500076C
.definelabel s_object_b2,               0x15000958

SZP("background/00", background_00)

#define BGMAP_S(b)
#define BGMAP_N(b, i)   SZP("bgmap/" + #b + "/" + #i, bgmap_##b##_##i)
#define BGMAP_E(b)      .seg szp_bgmap_##b##_end
#include "bgmap/course1.h"
#include "bgmap/course2.h"

SZP("texture/02", texture_02)

SZP("course", course)
SCR("course", course, 0x1A000000)

#define STAGE(name)                                     \
    SZP("stage/" + #name + "/gfx", stage_##name) ::     \
    SCR_STAGE("stage/" + #name, stage_##name, 0x0E000000)
STAGE(course1)
STAGE(course2)
STAGE(course3)
STAGE(end)

.seg seg_motion_player
.incbin "data/motion_player.bin"

.seg seg_demo
.incbin "data/demo.bin"

.seg seg_audio_ctl
.incbin "data/audio/ctl.bin"

.seg seg_audio_seq
.base 0
.incbin "data/audio/seq.bin"
#define SEQ(name)                                       \
    .align 4 ::                                         \
    seq_##name##_start:                                 \
    .incbin "data/audio/seq/" + #name + ".seq" ::       \
    .align 4 ::                                         \
    seq_##name##_end:
SEQ(mono0)
SEQ(mono1)
SEQ(mono2)
SEQ(stereo)
#undef SEQ

.seg seg_audio_bnk
.incbin "data/audio/bnk.bin"

.seg seg_audio_tbl
.incbin "data/audio/tbl.bin"

.orga scr_game_start
.base 0x15000000
.area 0x660, 0xFF
.importobj _BUILD + "/data/scr_game.o"
.endarea

.orga seg_audio_seq
.skip 0x04
#define SEQ(name)   .dw seq_##name##_start, seq_##name##_end-seq_##name##_start
.skip 0x08
.skip 0x08
SEQ(mono0)
SEQ(mono1)
.skip 0x08
SEQ(mono2)
SEQ(stereo)
SEQ(stereo)
SEQ(stereo)
.skip 0x08
SEQ(stereo)
SEQ(stereo)
#undef SEQ
.skip 0xBC
; 0x3020
.skip 0x1296
    ; .db 0xC6, 0x09
    .db 0xC1, 0x80
    .db 0xDA :: .dh 0x3358
    .db 0xD8, 0x03
    .db 0xD7, 0x3C
    .db 0xCC, 0x19
    .db 0xFC :: .dh 0x0144
    .db 0x90 :: .dh 0x11E4
    .db 0xFF

.orga seg_audio_bnk
.skip 0x46
.skip 0x0C
.skip 0x02
    .db 0x01, 0x0B ; 0x02 loop0
    .db 0x01, 0x0B ; 0x03 loop1
.skip 0x02
    .db 0x01, 0x13 ; 0x05 drumroll
    .db 0x01, 0x0C ; 0x06 title
    .db 0x01, 0x0E ; 0x07 win
    .db 0x01, 0x13 ; 0x08 lose
.skip 0x02
    .db 0x01, 0x10, 0x00 ; 0x0A course1
    .db 0x01, 0x12 ; 0x0B course2

.close
