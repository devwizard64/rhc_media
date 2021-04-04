#!/bin/sh

#                       rhc_media - Mario no Gourmetrace
#                        Copyright (C) 2020  devwizard
#         This project is licensed under the terms of the GNU General
#         Public License version 2.  See LICENSE for more information.

set -e
SEQ()
{
    ../../tools/armips -strequ _DST ../../data/audio/seq/$1.seq \
        -equ S $2 -equ L $3 -equ R $4 seq.asm
}
SEQ mono0    0 0 0
SEQ mono1    0 1 0
SEQ mono2    0 10 0
SEQ stereo   1 0 1
