/******************************************************************************
 *                      rhc_media - Mario no Gourmetrace                      *
 *                       Copyright (C) 2020  devwizard                        *
 *        This project is licensed under the terms of the GNU General         *
 *        Public License version 2.  See LICENSE for more information.        *
 ******************************************************************************/

#ifndef _GBI_EXT_H_
#define _GBI_EXT_H_

#include <ultra64.h>

#ifndef __ASSEMBLER__

#ifndef gsSP2Triangles
#define gsSP2Triangles(v00, v01, v02, flag0, v10, v11, v12, flag1) \
    gsSP1Triangle(v00, v01, v02, flag0), gsSP1Triangle(v10, v11, v12, flag1)
#endif

#define gsSPSetLights1N(name)                                                  \
    gsSPLight(&name.l[0],1),                                                   \
    gsSPLight(&name.a,2)

#define gDPSetFillColorRGB(pkt, r, g, b)                                       \
    gDPSetFillColor(pkt, 0x00010001U*GPACK_RGBA5551(r, g, b, 1))
#define gsDPSetFillColorRGB(r, g, b)                                           \
    gsDPSetFillColor(0x00010001U*GPACK_RGBA5551(r, g, b, 1))

#define gsDPLoadTextureBlockN(                                                 \
    fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt       \
)                                                                              \
    gsDPSetTile(                                                               \
        fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt,     \
        cms, masks, shifts                                                     \
    ),                                                                         \
    gsDPLoadSync(),                                                            \
    gsDPLoadBlock(                                                             \
        G_TX_LOADTILE, 0, 0,                                                   \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT)-1,                    \
        CALC_DXT(width, siz##_BYTES)                                           \
    ),                                                                         \
    gsDPPipeSync(),                                                            \
    gsDPSetTile(                                                               \
        fmt, siz, ((((width) * siz##_LINE_BYTES)+7)>>3), 0, G_TX_RENDERTILE,   \
        pal, cmt, maskt, shiftt, cms, masks, shifts                            \
    ),                                                                         \
    gsDPSetTileSize(                                                           \
        G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,            \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC                                   \
    )

#define gsDPLoadTextureTileN(                                                  \
    fmt, siz, width, height, uls, ult, lrs, lrt, pal, cms, cmt, masks, maskt,  \
    shifts, shiftt                                                             \
)                                                                              \
    gsDPSetTile(                                                               \
        fmt, siz, (((((lrs)-(uls)+1) * siz##_TILE_BYTES)+7)>>3), 0,            \
        G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts               \
    ),                                                                         \
    gsDPLoadSync(),                                                            \
    gsDPLoadTile(                                                              \
        G_TX_LOADTILE, (uls)<<G_TEXTURE_IMAGE_FRAC,                            \
        (ult)<<G_TEXTURE_IMAGE_FRAC, (lrs)<<G_TEXTURE_IMAGE_FRAC,              \
        (lrt)<<G_TEXTURE_IMAGE_FRAC                                            \
    ),                                                                         \
    gsDPPipeSync(),                                                            \
    gsDPSetTile(                                                               \
        fmt, siz, (((((lrs)-(uls)+1) * siz##_LINE_BYTES)+7)>>3), 0,            \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts           \
    ),                                                                         \
    gsDPSetTileSize(                                                           \
        G_TX_RENDERTILE, (uls)<<G_TEXTURE_IMAGE_FRAC,                          \
        (ult)<<G_TEXTURE_IMAGE_FRAC, (lrs)<<G_TEXTURE_IMAGE_FRAC,              \
        (lrt)<<G_TEXTURE_IMAGE_FRAC                                            \
    )

#define gDPLoadTextureBlock2(pkt, siz, width, height)                          \
{                                                                              \
    gDPLoadSync(pkt);                                                          \
    gDPLoadBlock(                                                              \
        pkt, G_TX_LOADTILE, 0, 0,                                              \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT)-1,                    \
        CALC_DXT(width, siz##_BYTES)                                           \
    );                                                                         \
}
#define gsDPSetTextureBlock2N(                                                 \
    fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt       \
)                                                                              \
    gsDPSetTile(                                                               \
        fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt,     \
        cms, masks, shifts                                                     \
    ),                                                                         \
    gsDPSetTile(                                                               \
        fmt, siz, ((((width) * siz##_LINE_BYTES)+7)>>3), 0, G_TX_RENDERTILE,   \
        pal, cmt, maskt, shiftt, cms, masks, shifts                            \
    ),                                                                         \
    gsDPSetTileSize(                                                           \
        G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,            \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC                                   \
    )
#define gsDPLoadTextureBlock2(siz, width, height)                              \
    gsDPLoadSync(),                                                            \
    gsDPLoadBlock(                                                             \
        G_TX_LOADTILE, 0, 0,                                                   \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT)-1,                    \
        CALC_DXT(width, siz##_BYTES)                                           \
    )

#define gDPSetTextureTile2(                                                    \
    pkt, timg, fmt, siz, width, twidth, pal, cms, cmt, masks, maskt, shifts,   \
    shiftt                                                                     \
)                                                                              \
{                                                                              \
    gDPSetTextureImage(pkt, fmt, siz, width, timg);                            \
    gDPSetTile(                                                                \
        pkt, fmt, siz, ((((twidth)*siz##_TILE_BYTES)+7) >> 3), 0,              \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts           \
    );                                                                         \
}
#define gDPLoadTextureTile2(pkt, uls, ult, lrs, lrt)                           \
{                                                                              \
    gDPLoadTile(                                                               \
        pkt, G_TX_RENDERTILE,                                                  \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                         \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrt) << G_TEXTURE_IMAGE_FRAC                                          \
    );                                                                         \
    gDPSetTileSize(                                                            \
        pkt, G_TX_RENDERTILE,                                                  \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                         \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrt) << G_TEXTURE_IMAGE_FRAC                                          \
    );                                                                         \
}
#define gsDPSetTextureTile2(                                                   \
    timg, fmt, siz, width, twidth, pal, cms, cmt, masks, maskt, shifts, shiftt \
)                                                                              \
    gsDPSetTextureImage(fmt, siz, width, timg),                                \
    gsDPSetTile(                                                               \
        fmt, siz, ((((twidth)*siz##_TILE_BYTES)+7) >> 3), 0, G_TX_RENDERTILE,  \
        pal, cmt, maskt, shiftt, cms, masks, shifts                            \
    )
#define gsDPLoadTextureTile2(uls, ult, lrs, lrt)                               \
    gsDPLoadTile(                                                              \
        G_TX_RENDERTILE,                                                       \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                         \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrt) << G_TEXTURE_IMAGE_FRAC                                          \
    ),                                                                         \
    gsDPSetTileSize(                                                           \
        G_TX_RENDERTILE,                                                       \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                         \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                         \
        (lrt) << G_TEXTURE_IMAGE_FRAC                                          \
    )

#define gsDPLoadTextureBlock_4bN(                                              \
    fmt, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt            \
)                                                                              \
    gsDPSetTile(                                                               \
        fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms,    \
        masks, shifts                                                          \
    ),                                                                         \
    gsDPLoadSync(),                                                            \
    gsDPLoadBlock(                                                             \
        G_TX_LOADTILE, 0, 0, (((width)*(height)+3)>>2)-1, CALC_DXT_4b(width)   \
    ),                                                                         \
    gsDPPipeSync(),                                                            \
    gsDPSetTile(                                                               \
        fmt, G_IM_SIZ_4b, ((((width)>>1)+7)>>3), 0, G_TX_RENDERTILE, pal, cmt, \
        maskt, shiftt, cms, masks, shifts                                      \
    ),                                                                         \
    gsDPSetTileSize(                                                           \
        G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,            \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC                                   \
    )

#define gDPFillRectangleSL(pkt, s, ulx, uly, lrx, lry)                         \
    gDPFillRectangle(                                                          \
        pkt, (ulx) << (s), (uly) << (s), ((lrx) << (s))-1, ((lry) << (s))-1    \
    )
#define gsDPFillRectangleSL(s, ulx, uly, lrx, lry)                             \
    gsDPFillRectangle(                                                         \
        (ulx) << (s), (uly) << (s), ((lrx) << (s))-1, ((lry) << (s))-1         \
    )

#define gDPFillRectangleSR(pkt, s, ulx, uly, lrx, lry)                         \
    gDPFillRectangle(                                                          \
        pkt, (ulx) >> (s), (uly) >> (s), ((lrx) >> (s))-1, ((lry) >> (s))-1    \
    )

#endif /* __ASSEMBLER__ */

#endif /* _GBI_EXT_H_ */
