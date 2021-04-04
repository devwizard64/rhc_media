#                       rhc_media - Mario no Gourmetrace
#                        Copyright (C) 2020  devwizard
#         This project is licensed under the terms of the GNU General
#         Public License version 2.  See LICENSE for more information.

import sys

stdout = sys.stdout
sys.stdout = open("/dev/null", "w")
import pygame
sys.stdout.close()
sys.stdout = stdout
del stdout

def tile(t, ch, cs, ck):
    src = pygame.image.load("%s.png" % t)
    src.set_colorkey(ck)
    i = 0
    for y in range(0, src.get_height(), ch+cs):
        dst = pygame.Surface((src.get_width(), ch), pygame.SRCALPHA)
        dst.blit(src, (0, -y))
        pygame.image.save(dst, "%s_%d.png" % (t, i))
        i += 1

def main():
    ck = (0x65, 0x8d, 0xd1)
    tile("wa", 48, 2, ck)
    tile("wb", 72, 2, ck)
    return 0

if __name__ == "__main__":
    sys.exit(main())
