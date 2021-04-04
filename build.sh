#!/bin/bash

#                       rhc_media - Mario no Gourmetrace
#                        Copyright (C) 2020  devwizard
#         This project is licensed under the terms of the GNU General
#         Public License version 2.  See LICENSE for more information.

set -x
set -e
#$ TIME=$(date "+%y-%m-%d %H:%M:%S")
BUILD=build
LABEL="Blandest"
TARGET=rhc_media
DST=$BUILD/$TARGET.z64
SYM=$BUILD/$TARGET.sym
BPS=$BUILD/$TARGET.bps
DEBUG="-O0 -fno-inline -D static="
CC="mips-linux-gnu-gcc -march=vr4300 -mfix4300 -mno-abicalls -mno-shared
    -mdivide-breaks -G 0 -fno-stack-protector -fno-common -fno-PIC
    -ffreestanding -fno-builtin -fwrapv -Wall -Wextra -Wpedantic
    -I $BUILD -I include -I src -I data"
CPP="mips-linux-gnu-cpp -P -I $BUILD -I include -I src -I data"
LD="mips-linux-gnu-ld"
NM="mips-linux-gnu-nm"
OBJCOPY="mips-linux-gnu-objcopy"
MKDIR()
{
    if [ ! -d $1 ]
    then
        mkdir $1
    fi
}
TEXTURE()
{
    O=$BUILD/texture/${1%.*}.h
    tools/texture $O texture/$1 $2
}
SHAPE()
{
    O=$BUILD/shape/${1%.*}
    MKDIR $O
    tools/shape $O shape/$1 "${@:2}"
}
CC()
{
    O=$BUILD/src/${1%.*}.o
    $CC "${@:2}" -Os -c -o $O src/$1
    if [[ $1 == */* ]]
    then
        L=O${1%/*}
    else
        L=Osrc
    fi
    printf -v $L "%s" "${!L} $O"
}
SCR()
{
    O=$BUILD/data/${1%.*}.o
    $CC "${@:2}" -D _SCRIPT -c -o $O data/$1
}
SLIENC()
{
    tools/mio0 $1.mio0 $2
    tools/mksz $1.mksz $2
    mio0=$(stat --format=%s $1.mio0)
    mksz=$(stat --format=%s $1.mksz)
    if [[ $mio0 < $mksz ]]
    then
        mv $1.mio0 $1
        rm $1.mksz
    else
        mv $1.mksz $1
        rm $1.mio0
    fi
}
SZP()
{
    O=$BUILD/data/${1%.*}
    $CC "${@:3}" -c -o $O.o data/$1
    $LD -n -Tdata=$2 -T szp.ld -o $O.elf $O.o
    $NM -g -n $O.elf > $O.map
    $OBJCOPY -O binary $O.elf $O.bin
    tools/map $O.asm $O.map
    SLIENC $O.szp $O.bin
    #$ $OBJCOPY -I binary -O elf32-big $O.szp $O.szp.o
}
SZP_BIN()
{
    O=$BUILD/data/${1%.*}
    SLIENC $O.szp data/$1
    touch $O.asm
}
SZP_ASM()
{
    O=$BUILD/data/${1%.*}
    tools/armips -strequ _BUILD $BUILD data/$1
    SLIENC $O.szp $O.bin
    touch $O.asm
}
STAGE()
{
    O=$BUILD/data/stage/$1
    SZP stage/$1/gfx.c 0x07000000
    SCR stage/$1/scr.S
    SCR stage/$1/gfx.c
}
BGMAP()
{
    MKDIR $BUILD/texture/bgmap/$1
    MKDIR $BUILD/data/bgmap/$1
    for ((i = 0; i < $2; i++))
    do
        TEXTURE bgmap/$1/$i.png rgba16
        SZP bgmap/$1/$i.c 0x00000000
    done
}

#$ tools/audio data/audio assets/audio.z64

MKDIR build
MKDIR $BUILD
MKDIR $BUILD/texture
MKDIR $BUILD/shape
MKDIR $BUILD/src
MKDIR $BUILD/data

SCR scr_main.S
SZP_ASM gfx_main.asm

MKDIR $BUILD/data/object
SZP_BIN object/gfx_player.bin
SZP_BIN object/gfx_a2.bin
SZP_BIN object/gfx_b2.bin
SZP_BIN object/gfx_c0.bin
SZP_BIN object/gfx_entity.bin

MKDIR $BUILD/texture/menu
MKDIR $BUILD/shape/menu
MKDIR $BUILD/data/menu
TEXTURE menu/logo.png rgba16
SHAPE menu.obj -g
SZP menu/gfx.c 0x07000000
SCR menu/scr.S
SCR menu/gfx.c

SCR scr_game.S

MKDIR $BUILD/data/background
SZP_BIN background/00.bin

MKDIR $BUILD/texture/bgmap
MKDIR $BUILD/data/bgmap
BGMAP course1 78
BGMAP course2 114
CC bgmap.c

MKDIR $BUILD/data/texture
SZP_BIN texture/02.bin

MKDIR $BUILD/texture/course
MKDIR $BUILD/texture/course/font
TEXTURE course/font/zero.png    rgba16
TEXTURE course/font/one.png     rgba16
TEXTURE course/font/two.png     rgba16
TEXTURE course/font/three.png   rgba16
TEXTURE course/font/four.png    rgba16
TEXTURE course/font/five.png    rgba16
TEXTURE course/font/six.png     rgba16
TEXTURE course/font/seven.png   rgba16
TEXTURE course/font/eight.png   rgba16
TEXTURE course/font/nine.png    rgba16
TEXTURE course/font/a.png       rgba16
TEXTURE course/font/c.png       rgba16
TEXTURE course/font/d.png       rgba16
TEXTURE course/font/e.png       rgba16
TEXTURE course/font/g.png       rgba16
TEXTURE course/font/h.png       rgba16
TEXTURE course/font/i.png       rgba16
TEXTURE course/font/k.png       rgba16
TEXTURE course/font/l.png       rgba16
TEXTURE course/font/n.png       rgba16
TEXTURE course/font/o.png       rgba16
TEXTURE course/font/p.png       rgba16
TEXTURE course/font/r.png       rgba16
TEXTURE course/font/t.png       rgba16
TEXTURE course/font/y.png       rgba16
TEXTURE course/font/exclaim.png rgba16
TEXTURE course/font/colon.png   rgba16
SZP course.c 0x0B000000
SCR course.S
CC course.c
CC opponent.c

MKDIR $BUILD/texture/stage
MKDIR $BUILD/shape/stage
MKDIR $BUILD/data/stage

MKDIR $BUILD/texture/stage/course1
MKDIR $BUILD/data/stage/course1
TEXTURE stage/course1/bg.png rgba16
TEXTURE stage/course1/wa_0.png rgba16
TEXTURE stage/course1/wa_1.png rgba16
TEXTURE stage/course1/wa_2.png rgba16
TEXTURE stage/course1/wa_3.png rgba16
TEXTURE stage/course1/wa_4.png rgba16
TEXTURE stage/course1/wa_5.png rgba16
TEXTURE stage/course1/wb_0.png rgba16
TEXTURE stage/course1/wb_1.png rgba16
TEXTURE stage/course1/wb_2.png rgba16
TEXTURE stage/course1/wb_3.png rgba16
TEXTURE stage/course1/wb_4.png rgba16
TEXTURE stage/course1/wb_5.png rgba16
M1=1,0,0,0,0,1.0625,0,0,0,0,1,0,4822,-4096,0,1
M2=1,0,0,0,0,1.0625,0,0,0,0,1,0,-4492,0,0,1
SHAPE stage/course1.obj \
    obj=w1 -m m=$M1 \
    obj=path1 -p m=$M1 \
    obj=box1 -p m=$M1 \
    obj=coin1 -p m=$M1 \
    obj=water1 -b m=$M1 \
    obj=water2 -b m=$M1 \
    obj=w2 -m m=$M2 \
    obj=path2 -p m=$M2 \
    obj=box2 -p m=$M2 \
    obj=coin2 -p m=$M2 \
    obj=mcoin2 -p m=$M2
STAGE course1

MKDIR $BUILD/texture/stage/course2
MKDIR $BUILD/data/stage/course2
TEXTURE stage/course2/bg.png rgba16
M1=1,0,0,0,0,1.0625,0,0,0,0,1,0,9320,-4096,0,1
M2=1,0,0,0,0,1.0625,0,0,0,0,1,0,160,0,0,1
M3=1,0,0,0,0,1.0625,0,0,0,0,1,0,-9496,4096,0,1
SHAPE stage/course2.obj \
    obj=w1 -m m=$M1 \
    obj=path1 -p m=$M1 \
    obj=coin1 -p m=$M1 \
    obj=mcoin1 -p m=$M1 \
    obj=w2 -m m=$M2 \
    obj=path2 -p m=$M2 \
    obj=coin2 -p m=$M2 \
    obj=mcoin2 -p m=$M2 \
    obj=w3 -m m=$M3 \
    obj=path3 -p m=$M3 \
    obj=coin3 -p m=$M3 \
    obj=mcoin3 -p m=$M3
STAGE course2

MKDIR $BUILD/data/stage/course3
#$ SHAPE stage/course3.obj
SZP_BIN stage/course3/gfx.bin
SCR stage/course3/scr.S
SCR stage/course3/gfx.c

MKDIR $BUILD/texture/stage/end
MKDIR $BUILD/data/stage/end
TEXTURE stage/end/logo.png i8
STAGE end

$LD -r -o $BUILD/main3.o $Osrc
$CPP -o $BUILD/main.asm main.asm
tools/armips -strequ _BUILD $BUILD -strequ _LABEL "$LABEL" -strequ _DST $DST \
    -sym $SYM $BUILD/main.asm
tools/crc $DST
#$ tools/sym $HOME/sm64/Project64/Save/"$LABEL".sym $SYM
#$ tools/flips -c -b donor/UNSME0.z64 $DST $BPS > /dev/null
