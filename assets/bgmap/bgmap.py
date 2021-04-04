#                       rhc_media - Mario no Gourmetrace
#                        Copyright (C) 2020  devwizard
#         This project is licensed under the terms of the GNU General
#         Public License version 2.  See LICENSE for more information.

import sys
import os

stdout = sys.stdout
sys.stdout = open("/dev/null", "w")
import pygame
sys.stdout.close()
sys.stdout = stdout
del stdout

def mkdir(fn):
    if not os.path.isdir(fn):
        os.mkdir(fn)

def bgmap(b):
    ch = 64
    src = pygame.image.load("%s.png" % b)
    h = src.get_height()
    i = 0
    buf = "BGMAP_S(%s)\n" % b
    for y in range(0, h, ch):
        mkdir("../../texture/bgmap/%s" % b)
        mkdir("../../data/bgmap/%s" % b)
        dst = pygame.Surface((src.get_width(), min(ch, h)), pygame.SRCALPHA)
        dst.blit(src, (0, -y))
        pygame.image.save(dst, "../../texture/bgmap/%s/%d.png" % (b, i))
        data = (
            "#include <ultra64.h>\n"
            "#include <gbi_ext.h>\n"
            "#include <sm64.h>\n"
            "\n"
            "const u16 texture_bgmap_%s_%d[] =\n"
            "{\n"
            "#include \"texture/bgmap/%s/%d.h\"\n"
            "};\n"
        ) % (b, i, b, i)
        with open("../../data/bgmap/%s/%d.c" % (b, i), "w") as f:
            f.write(data)
        buf += "BGMAP_N(%s, %d)\n" % (b, i)
        i += 1
        h -= ch
    buf += "BGMAP_E(%s)\n" % b
    with open("../../data/bgmap/%s.h" % b, "w") as f:
        f.write(buf)

def main():
    mkdir("../../texture/bgmap")
    mkdir("../../data/bgmap")
    bgmap("course1")
    bgmap("course2")
    return 0

if __name__ == "__main__":
    sys.exit(main())
