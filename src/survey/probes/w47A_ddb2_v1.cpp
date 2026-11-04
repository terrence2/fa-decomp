/* rva 355360 v1: DoubleDecodeDBook — double-height variant of DecodeDBook.
 * Same gradient block (gd->c1ba gate; d14/d16 = bits[4]/bits[5]*8/5; f0 = the
 * negated 16-bit sum of the shifted gradients). mode2 picks the 15-bit color
 * mask (0x7bde when mode2 == 0xf, else 0xf7de; FA materializes it branchlessly
 * via sub-0xf/cmp-1/sbb/and-0xffff8400/add-0xf7de). Each iteration decodes 4
 * clamp-pixel blocks (3 calls to the nameless clamp chunk 0x456c00 each):
 *  odd blocks (1,3) keep green in a register and pack px into bx;
 *  even blocks (2,4) park green at frame-4 via the call-shadow slot (the
 *  result store `mov %ax,0x18(%esp)` executes while the clamp arg push is
 *  live, i.e. one dword below final esp) and pack px into bp.
 * Pixel pairs are written as: dst[0]=pxA, then backfill dst[1..3] =
 * (pxA&mask, pxB, pxB&mask), and when mode1 != 0 four more stores
 * dst[0..3] = (pxA&mask, pxA, pxB&mask, pxB) for the second row.
 * Compiled compactly (loop over the 4 blocks) so CL .text stays under the
 * 1104-B chunk bound; the whole-body transplant replaces the body (see
 * w47A_final.json provenance). */
typedef struct {
    unsigned char _p[0xc1b4];
    short c1b4;
    short c1b6;
    short c1b8;
    unsigned short c1ba;
} GlobalData;

extern "C" unsigned short __cdecl w31b_56c00_v2(unsigned short);

void __cdecl DoubleDecodeDBook(unsigned char *bits, unsigned short *dst,
                               unsigned short mode1, unsigned short mode2,
                               GlobalData *gd)
{
    unsigned short mask, f0, d14, d16, v, cnt;
    unsigned short px1, px2, bval;
    unsigned short b;

    mask = 0xf7de;
    if (mode2 == 0xf)
        mask = 0x7bde;
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
        for (b = 0; b < 4; b++) {
            v = (int)(*bits++ * gd->c1b4) / 16;
            px1 = w31b_56c00_v2(gd->c1b6 + v + d14 + 4);
            px2 = w31b_56c00_v2(v + f0 + 4);
            bval = w31b_56c00_v2(gd->c1b8 + v + d16 + 4);
            if (mode2 == 0xf) {
                px1 &= 0xfff8;
                px1 <<= 5;
                px1 |= px2;
                px1 &= 0xfff8;
                px1 <<= 2;
            } else {
                px1 &= 0xfff8;
                px1 <<= 8;
                px1 |= px2 << 3;
                px1 &= 0xffe0;
            }
            px1 |= bval >> 3;
            *dst = px1;
            dst++;
            if (b & 1) {
                dst[0] = px1 & mask;
                dst[1] = px1;
                dst[2] = px2 & mask;
                dst[3] = px2;
                dst += 4;
            } else {
                dst[-2] = px1 & mask;
                dst[-1] = px2 & mask;
                dst++;
            }
        }
        bits += 2;      /* bits[4]/bits[5] dither params consumed */
    } while (--cnt);
}