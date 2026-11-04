// _DecodeInterSVGA15Frame @ rva 0x589e0 (1936 B) — wave 47 batch C
//
// Interleaved sibling of _DecodeSVGA15Frame / _DecodeInterSVGA15NONFrame
// (15bpp variant: the Copy*15 helpers move 8 table dwords as double-width
// 16bpp pixel pairs). FPO params=3 dwords, locals frame 0x2b0 (esp-frame,
// no EBP; ebx/esi/edi/ebp pushed after the sub), no SEH.
// arg1 = VESA state struct (u32s @+0x20/+0x24/+0x28/+0x2c, u32 cursor
// @+0xc044, u16 dst arrays @+0x44/+0x2044/+0x4044); arg2 = FrameHeader
// (u16s @+0xa i1 / +0xc i2 / +0xe i3 / +0x10 i5 / +0x12 i4 / +0x14 i6);
// arg3 = GlobalData (u16 @+0xc142, u16 @+0xc144, ptr @+0xc14e -> plane
// u16s @+4 x0 / +6 x1 and u8 mode @+0x19, u32 @+0xc19c, ptrs @+0xc1a0 /
// +0xc1a4 = bitstream / tilestream plane offsets, ptr @+0xc1a8 =
// 0x2000-dword temp row buffer).
//
// Verified calls (dis 0x4589e0..0x459169; all 8 rel32 targets are layout
// chunks; zero FA .reloc entries over the span):
//   DecodeDBook x2, DoubleDecodeDBook, SetVESABank x3, _CopyDB15, _CopySB15.
// Tail pad 6 B (8d9b00000000).
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex") — FA's esp-frame
// register schedule (esi = u16 pixel walker in the tile loop AND temp-row
// src walker in the interlace phase, esi/edi double duty, ebp = tile counter
// in one context and bp16 in another), the MSB-first mask refills and the
// 312-entry u16 pixel scratch read back as u8 gate bytes (pix8[tile_no]) are
// not steerable in natural C.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern void __cdecl DecodeDBook(u8 *src, u16 *dst, u16 mode, void *gd);
extern void __cdecl DoubleDecodeDBook(u8 *src, u16 *dst, u8 g3, u16 mode, void *gd);
extern u16 __cdecl SetVESABank(u16 bank);
extern void __cdecl CopyDB15(void *tbl, u16 *dst, u8 *idx, u16 stride);
extern void __cdecl CopySB15(u8 *tbl, u16 *dst, u16 stride);

#define A32(p, o) (*(u32 *)((char *)(p) + (o)))
#define A16(p, o) (*(u16 *)((char *)(p) + (o)))

void DecodeInterSVGA15Frame(void *a, void *fh, void *gd)
{
    u16 pix[312];             /* frame 0x40..0x2b0: u16 pixels in the tile loop,
                                 their LOW bytes re-read as copy gates in the
                                 interlace phase (pix8[tile_no]) */
    u16 *pw;                  /* pixel walker (esi) */
    u16 i1, i2, i3, i5, i4, i6, mode;
    u16 *p0;                  /* GlobalData @+0xc14e */
    u8 *bits, *tiles;         /* frame 0x28 / 0x2c (persist across rows) */
    u32 mask, word32;         /* frame 0x20 / 0x38 (persist across rows) */
    u32 offv, r7, r5, x0, x1, t, dst, src, v, j;
    u16 bankval;              /* frame 0x1a (E-0x2a6) */
    u16 tval;                 /* frame 0x1e (E-0x2a2) */
    u16 b32;                  /* frame 0x30: bankval copy, then bank counter */
    u16 n20h, diffn, shiftcnt;
    u16 flag01;               /* frame 0x10: interlace-phase flag */
    u16 c1;                   /* frame 0x10 again: block-A/C count (alias) */
    short s14;                /* frame 0x14: phase-1 accumulator */
    short bp16;               /* block-A budget (ebp) */
    short bx16;               /* block-B/C budget (bx) */
    u16 dx;                   /* block-B/C copy count */
    u32 gate;                 /* pix8 gate index */
    u32 *tbuf;

    i1 = A16(fh, 0x0a);
    i2 = A16(fh, 0x0c);
    i3 = A16(fh, 0x0e);
    i5 = A16(fh, 0x10);
    i4 = A16(fh, 0x12);
    i6 = A16(fh, 0x14);
    p0 = (u16 *)A32(gd, 0xc14e);
    mode = (u16)*((u8 *)p0 + 0x19);

    /* bitstream = fh + P + i4 + 6*(i1+i2+i3) + 24; tilestream = + i5 */
    bits = (u8 *)fh + A32(gd, 0xc1a0) + i4 + 6u * (i1 + i2 + i3) + 24;
    tiles = bits + i5;

    if (i2 != 0) {
        DecodeDBook((u8 *)fh + A32(gd, 0xc1a4) + i4 + 6u * i1 + 24,
                    (u16 *)((char *)a + 0x2044), mode, gd);
        DecodeDBook((u8 *)fh + A32(gd, 0xc1a4) + i4 + 24,
                    (u16 *)((char *)a + 0x44), mode, gd);
        A32(a, 0xc044) = (u32)((char *)a + 0x44);
        DoubleDecodeDBook((u8 *)fh + A32(gd, 0xc1a4) + i4
                              + 12u * (i1 + i2) + 48,
                          (u16 *)((char *)a + 0x4044), 1, mode, gd);
    }

    offv = ((A32(a, 0x2c) + A32(gd, 0xc19c)) * (u32)A16(gd, 0xc142)
            + A32(a, 0x28)) * 2;
    tbuf = (u32 *)A32(gd, 0xc1a8);
    for (j = 0; j < 0x2000u; j++)
        tbuf[j] = 0;

    shiftcnt = 0;
    v = (u32)A16(p0, 4) << 9;
    while (v != 0) {
        v >>= 1;
        shiftcnt++;
    }

    bankval = SetVESABank((u16)(offv >> shiftcnt));
    r5 = A16(gd, 0xc144);
    if (A32(a, 0x24) < r5)
        r5 = A32(a, 0x24);
    flag01 = 0;
    if (r5 == 0)
        return;

    for (r7 = 0; r7 < r5; r7 += 4) {
        if (r7 >= i6)
            A32(a, 0xc044) = (u32)((char *)a + 0x2044);
        x0 = A16(p0, 4);                    /* esi := x0 */
        b32 = bankval;                      /* frame 0x30 */
        t = x0 * b32;
        dst = offv + ((u32)A16(gd, 0xc142) - (t << 7)) * 8;
        x1 = A16(p0, 6);
        if (dst > (x1 << 10)) {
            flag01 = 1;                     /* frame 0x10 */
            dst = A32(gd, 0xc1a8);
        } else {
            dst = offv + ((0x280u - t) << 10);
        }

        /* tile loop: 4 bytes of tile data per iteration over a->f20;
           ebx = dst walker, esi = pix walker, edi = tile no. (gate index) */
        mask = 0;
        for (j = 0; j < A32(a, 0x20); j += 4) {
            pw = pix + j / 4;
            if (mask == 0) {
                mask = 0x80000000u;
                word32 = *(u32 *)bits;
                bits += 4;
            }
            if ((word32 & mask) != 0) {
                mask >>= 1;
                *pw = 0xffff;
                if (mask == 0) {
                    mask = 0x80000000u;
                    word32 = *(u32 *)bits;
                    bits += 4;
                }
                if ((word32 & mask) != 0) {
                    CopyDB15((void *)A32(a, 0xc044), (u16 *)dst, tiles,
                             (u16)(2 * A16(gd, 0xc142)));
                    tiles += 4;
                } else {
                    u8 b = *tiles++;
                    CopySB15((u8 *)((char *)a + 0x4044) + ((u32)b << 5),
                             (u16 *)dst, (u16)(2 * A16(gd, 0xc142) - 4));
                }
                mask >>= 1;
            } else {
                *pw = 0;
            }
            dst += 8;
        }

        /* interlace phase: shovel the 0x2000-dword temp rows back over the
           banked frame in run-length blocks, gated by pix8[] */
        if (flag01 != 0) {
            bp16 = (short)(u16)((((x0 * b32 + x1) << 10) - offv) >> 2);
            b32 = (u16)(offv >> shiftcnt);
            bx16 = (short)(u16)(2 * A16(gd, 0xc142) - (u16)bp16);
            bankval = SetVESABank(b32);
            dst = offv + ((0x280u - x0 * (u32)bankval) << 10);
            src = A32(gd, 0xc1a8);
            s14 = 0;
            c1 = 0;
            n20h = (u16)(A32(a, 0x20) >> 1);
            diffn = (u16)(A16(gd, 0xc142) / 2 - n20h);
            /* block A: walk the bp16 budget in n20h/diffn runs (gate index
               resets at each run head) */
            if (bp16 > 0) {
                do {
                    gate = 0;
                    if (n20h <= bp16) {
                        c1 = n20h;
                        tval = diffn;
                    } else {
                        tval = 0;
                        c1 = bp16;
                    }
                    bp16 -= (short)(tval + c1);
                    s14 += (short)(tval + c1);
                    for (j = 0; (u32)j < (u32)c1; j++) {
                        if (((u8 *)pix)[gate] != 0) {
                            *(u32 *)dst = *(u32 *)src;
                            src += 4;
                        }
                        dst += 4;
                        src += 4;
                        gate++;
                    }
                    dst += (u32)((short)tval << 2);
                    src += (u32)((short)tval << 2);
                } while (bp16 > 0);
            }
            bankval = SetVESABank((u16)(b32 + 1));
            if (bx16 != 0) {
                dst = offv + (((0x280u - x0 * (u32)bankval) << 8)
                              + (u32)(short)s14) * 4;
                if (tval == 0) {
                    /* block B1 (gate index continues from block A) */
                    dx = (u16)(n20h - c1);
                    bx16 -= (short)(diffn + dx);
                    for (j = 0; (u32)j < (u32)dx; j++) {
                        if (((u8 *)pix)[gate] != 0) {
                            *(u32 *)dst = *(u32 *)src;
                            src += 4;
                        }
                        dst += 4;
                        src += 4;
                        gate++;
                    }
                    dst += (u32)((short)diffn << 2);
                    src += (u32)((short)diffn << 2);
                }
                if (tval != 0)
                    bx16 += bp16;               /* block C' */
                if (bx16 > 0) {
                    /* blocks C / C': one 0-based gate sweep per outer run */
                    while (bx16 > 0) {
                        u32 gate = 0;
                        if (n20h <= bx16) {
                            c1 = n20h;
                            tval = diffn;
                        } else {
                            tval = 0;
                            c1 = bx16;
                        }
                        bx16 -= (short)(tval + c1);
                        for (j = 0; (u32)j < (u32)c1; j++) {
                            if (((u8 *)pix)[gate] != 0) {
                                *(u32 *)dst = *(u32 *)src;
                                src += 4;
                            }
                            dst += 4;
                            src += 4;
                            gate++;
                        }
                        dst += (u32)((short)tval << 2);
                        src += (u32)((short)tval << 2);
                    }
                }
            }
        }
        c1 = 0;
        offv += (u32)A16(gd, 0xc142) * 8;
    }
}