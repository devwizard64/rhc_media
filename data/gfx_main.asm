;                       rhc_media - Mario no Gourmetrace
;                        Copyright (C) 2020  devwizard
;         This project is licensed under the terms of the GNU General
;         Public License version 2.  See LICENSE for more information.

.open "data/gfx_main.bin", _BUILD + "/data/gfx_main.bin", 0x02000000
.include "include/ultra64.asm"
.include "include/sm64.asm"
.table "include/sm64.tbl"

.org 0x02007700
.skip 0x84
    .dw texture_print_x

.org 0x02010D14
.area 0x254, 0xFF
str_1_pumpkin_grand:
    .str " 1 PUMPKIN GRAND"
str_2_battleship_halberd:
    .str " 2 BATTLESHIP HALBERD"
str_3_bob_omb_battlefield:
    .str " 3 BOB-OMB BATTLEFIELD"
.endarea
.area 0x6C, 0x00
    .dw str_1_pumpkin_grand
    .dw str_2_battleship_halberd
    .dw str_3_bob_omb_battlefield
.endarea
.area 0x958, 0xFF
texture_print_x:
    .incbin "data/print_x.bin"
str_vs_koopa_the_quick:
    .str "VS. KOOPA THE QUICK"
.endarea
.area 0x188, 0x00
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
    .dw str_vs_koopa_the_quick
.endarea

.close
