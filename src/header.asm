;                       rhc_media - Mario no Gourmetrace
;                        Copyright (C) 2020  devwizard
;         This project is licensed under the terms of the GNU General
;         Public License version 2.  See LICENSE for more information.

.db 0x80, 0x37, 0x12, 0x40
.dw 0x0000000F
.dw main_start
.fill 0x02, 0x00
.db 20, 'D'
.dw 0xFFFFFFFF, 0xFFFFFFFF
.fill 0x08, 0x00
.area 0x14, ' '
.ascii _LABEL
.endarea
.fill 0x07, 0x00
.ascii "N"
.ascii "SM"
.ascii "E"
.db 0x00
