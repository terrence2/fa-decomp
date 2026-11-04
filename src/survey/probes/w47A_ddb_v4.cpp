/* rva 354384 v3: struct-locals (dead 2-B pad = FA frame hole) + short d14/d16
 * for FA's movswl extension in the f0 gradient sum; arg sums stay ushort-
 * narrowed (CL keeps 66-prefixed adds). */
typedef struct {
    unsigned char _p[0xc1b4];
    short c1b4;
    short c1b6;
    short c1b8;
    unsigned short c1ba;
} GlobalData;

extern "C" unsigned short __cdecl w31b_56c00_v2(unsigned short);

void __cdecl DecodeDBook(unsigned char *bits, unsigned short *dst,
                         unsigned short mode, GlobalData *gd)
{
    unsigned short hole;   /* FA frame bytes 0-1 — never touched */
    short f0, d14, d16;
    unsigned short green, v, cnt;
    unsigned short px, bval;

    cnt = 0x100;
    do {
        if (gd->c1ba != 0) {
            f0 = 0;
            d16 = 0;
            d14 = 0;
        } else {
            d14 = bits[4] * 8 / 5;
            d16 = bits[5] * 8 / 5;
            f0 = -(short)((short)((gd->c1b8 + d16) >> 2)
                          + (short)((gd->c1b6 + d14) >> 1));
        }
        v = (int)(*bits++ * gd->c1b4) / 16;
        px = w31b_56c00_v2(gd->c1b6 + v + d14 + 4);
        green = w31b_56c00_v2(v + f0 + 4);
        bval = w31b_56c00_v2(gd->c1b8 + v + d16 + 4);
        if (mode == 0xf) {
            px &= 0xfff8;
            px <<= 5;
            px |= green;
            px &= 0xfff8;
            px <<= 2;
        } else {
            px &= 0xfff8;
            px <<= 8;
            px |= green << 3;
            px &= 0xffe0;
        }
        px |= bval >> 3;
        *dst++ = px;

        v = (int)(*bits++ * gd->c1b4) / 16;
        px = w31b_56c00_v2(gd->c1b6 + v + d14 + 4);
        green = w31b_56c00_v2(v + f0 + 4);
        bval = w31b_56c00_v2(gd->c1b8 + v + d16 + 4);
        if (mode == 0xf) {
            px &= 0xfff8;
            px <<= 5;
            px |= green;
            px &= 0xfff8;
            px <<= 2;
        } else {
            px &= 0xfff8;
            px <<= 8;
            px |= green << 3;
            px &= 0xffe0;
        }
        px |= bval >> 3;
        *dst++ = px;

        v = (int)(*bits++ * gd->c1b4) / 16;
        px = w31b_56c00_v2(gd->c1b6 + v + d14 + 4);
        green = w31b_56c00_v2(v + f0 + 4);
        bval = w31b_56c00_v2(gd->c1b8 + v + d16 + 4);
        if (mode == 0xf) {
            px &= 0xfff8;
            px <<= 5;
            px |= green;
            px &= 0xfff8;
            px <<= 2;
        } else {
            px &= 0xfff8;
            px <<= 8;
            px |= green << 3;
            px &= 0xffe0;
        }
        px |= bval >> 3;
        *dst++ = px;

        v = (int)(*bits++ * gd->c1b4) / 16;
        px = w31b_56c00_v2(gd->c1b6 + v + d14 + 4);
        green = w31b_56c00_v2(v + f0 + 4);
        bval = w31b_56c00_v2(gd->c1b8 + v + d16 + 4);
        if (mode == 0xf) {
            px &= 0xfff8;
            px <<= 5;
            px |= green;
            px &= 0xfff8;
            px <<= 2;
        } else {
            px &= 0xfff8;
            px <<= 8;
            px |= green << 3;
            px &= 0xffe0;
        }
        px |= bval >> 3;
        *dst++ = px;
        bits += 2;      /* bits[4]/bits[5] dither params consumed */
    } while (--cnt);
}