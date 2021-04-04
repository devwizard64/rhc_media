;                       rhc_media - Mario no Gourmetrace
;                        Copyright (C) 2020  devwizard
;         This project is licensed under the terms of the GNU General
;         Public License version 2.  See LICENSE for more information.

.create _DST, 0
.n64
    .db 0xD3, 0x20
    .db 0xD7 :: .dh S ? 0x0003 : 0x0001
    .db 0xDB, 0x58
@@loop:
    .db 0x90 :: .dh chn_0
.if S
    .db 0x91 :: .dh chn_1
.endif
    .db 0xDD, 0x00
    .db 0xFD :: .dh 0xFFFF
    .db 0xFB :: .dh @@loop
    .db 0xD6 :: .dh S ? 0x0003 : 0x0001
    .db 0xFF
chn_0:
    .db 0xC4
    .db 0x90 :: .dh trk_0
.if S
    .db 0xDD, 0x00
.endif
    .db 0xC1, L
    .db 0xFD :: .dh 0xFFFF
    .db 0xFF
trk_0:
    .db 0xC2, 0x00
    .db 0x67 :: .dh 0xFFFF :: .db 0x7F
    .db 0xFF
.if S
chn_1:
    .db 0xC4
    .db 0x90 :: .dh trk_0
    .db 0xDD, 0x80
    .db 0xC1, R
    .db 0xFD :: .dh 0xFFFF
    .db 0xFF
trk_1:
    .db 0xC2, 0x00
    .db 0x67 :: .dh 0xFFFF :: .db 0x7F
    .db 0xFF
.endif
.close
