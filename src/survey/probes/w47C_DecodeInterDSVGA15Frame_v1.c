// _DecodeInterDSVGA15Frame @ rva 0x59170 (1984 B) — wave 47 batch C
// Interlaced doubled sibling of _DecodeDSVGA15Frame (0x57430); FPO
// locals=332 B (esp+0x40..0x167 = 74-dword mask + scratch), params=3,
// cbProlog=0x14 (sub esp,0x530 + 4 pushes), no SEH, epilogue
// pop ebp/edi/esi/ebx + add esp,0x530 + ret + 8b ff hotpad.
//
// args: state = u32* (+0x20/+0x28/+0x2c/+0x24 fields, +0x44/+0x2044/
// +0x4044 u16 windows, +0xc044 ptr), fh = FrameHeader* (u16 words +0xa/
// +0xc/+0xe/+0x10/+0x12/+0x14), gd = GlobalData* (+0xc142/+0xc144 u16,
// +0xc14e ptr, +0xc19c/+0xc1a0/+0xc1a4 u32, +0xc1a8 0x2000-dword scratch
// buffer).
//
// Calls (rel32 targets all in converted/nameless chunks; ZERO FA .reloc
// HIGHLOW entries over 0x59170..0x59930 — verified by walking FA/FA.EXE
// .reloc blocks — so the whole-body transplant ships no newsites and the
// baked e8 disp dwords stay VA-stable):
//   ?DoubleDecodeDBook@@YAXPAEPAGGGPAUGlobalData@@@Z x3 at 0x56c20
//     (u8* dst, u16* src, u16 sel, u16 flag, GlobalData*) — FA packs the
//     two ushort args, 5 dword pushes per call;
//   ?SetVESABank@@YAGG@Z x3 at 0x69fb0 — body is 66 33 c0 / c3 (return
//     0); ushort pair rides one dword push (high half ignored);
//   _CopyDDB15 at 0xc922c — 4 args (dst = *(state+0xc044), src, byte
//     walker, cnt = w142*4-4; walker += 4);
//   _CopyDSB15 at 0xc91a8 — 3 args (dst = state+0x4044 + walkerbyte*32,
//     src, cnt = w142*4-12; walker += 1).
//
// Body: prologue seeds two dither-stream walkers off *(gd+0xc1a0) +
// dblstep + fh, dblstep = (3*(w0c+w0e+w0a)+12)*2 (u8 walker seeded
// +w10, u32 walker +w12); three DoubleDecodeDBook calls decode the
// state-buffer dither bands; a 0x8000-byte scratch clear; a w<<9
// halving count seeded at w142 yields the SetVESABank shift. Per row
// (dword-indexed, steps of 4): c044 re-anchors to state+0x2044 after
// row w14; a bitstream (rolling counter + current dword, persisted
// across rows) builds the 74-dword mask (bit1 spans, bit2 selects the
// engine); the flag branch then copies clamped dword spans from the
// scratch buffer to dst = total + ((0x280-w4*junk16)<<10), gated per
// dword by mask bytes, skipping chunks of dy past the SetVESABank
// results, then a second pass for the remaining bp span. FA multiplies
// the row base by an UNINITIALIZED stack word (esp+0x1a) every row —
// kept as the uninitialized `junk16` below. Phase 2a's first copy loop
// CONTINUES the mask byte index left over from Y1's last span (FA does
// not reset it); Y1/Y2/Y3 spans reset it per span. All signed span
// tests are 16-bit; esi/dst step 4 per dword, res*4/dy*4 per skipped
// tail (s16-extended, matching FA movswl).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;
typedef          short s16;

extern void __cdecl DoubleDecodeDBook(u8 *dst, u16 *src, u16 sel,
                                      u16 flag, void *gd);
extern u16  __cdecl SetVESABank(u16 bank);   /* FA: ushort pair, 1 push */
extern void __cdecl CopyDDB15(void *dst, void *src, u8 *walker, u32 cnt);
extern void __cdecl CopyDSB15(void *dst, void *src, u32 cnt);

void DecodeInterDSVGA15Frame(u32 *state, u16 *fh, void *gd)
{
    u32  mask[0x4a];        /* esp+0x40: 74 dwords written, bytes read */
    u32  bitwalk;           /* esp+0x2c: u32 source walker (persists) */
    u32  bytwalk;           /* esp+0x30: u8 byte walker (persists) */
    u32  bitcnt;            /* esp+0x20: rolling bit counter */
    u32  curbits;           /* esp+0x38: current bitstream dword */
    u32  total;             /* esp+0x24: row dword offset, steps w142*16 */
    u32  lim;               /* esp+0x3c: min(gd w144, state rows) */
    u32  rowidx;            /* esp+0x34: row index in dwords, steps 4 */
    u32  wbase, c1a0v, c1a4, c1a8, dblstep;
    u32  prod, esi, dst, t, iter;
    u16  shift;             /* esp+0x14: seeded gd w142, ++ per halving */
    u16  flagv;             /* esp+0x28: out-of-frame flag */
    u16  y16;               /* esp+0x28 alias: bank row (u16) */
    u16  hword;             /* esp+0x1c: (u16)*(state+0x20) span limit */
    u16  dy;                /* esp+0x18: w142 - hword */
    u16  acc;               /* esp+0x16: copied dwords so far (wraps) */
    u16  prevdx;            /* esp+0x12: last Y1 span length */
    u16  res;               /* esp+0x1e: SetVESABank result / span skip */
    u16  edi16;             /* left span counter (16-bit in FA) */
    u16  bp16;              /* bottom span counter (16-bit in FA) */
    u16  bidx;              /* mask byte index (u16 in FA, bx/di) */
    u16  dx, j16;
    u32  junkw;             /* esp+0x1a: UNINITIALIZED in FA, read each row */
    u16  w0a = *(u16 *)((char *)fh + 0x0a);
    u16  w0c = *(u16 *)((char *)fh + 0x0c);
    u16  w0e = *(u16 *)((char *)fh + 0x0e);
    u16  w10 = *(u16 *)((char *)fh + 0x10);
    u16  w12 = *(u16 *)((char *)fh + 0x12);
    u16  w14 = *(u16 *)((char *)fh + 0x14);
    u16  w142 = *(u16 *)((char *)gd + 0xc142);
    u16  w144;
    u8   flagb = *(u8 *)(*(u32 *)((char *)gd + 0xc14e) + 0x19);

    c1a0v = *(u32 *)((char *)gd + 0xc1a0);
    c1a4 = *(u32 *)((char *)gd + 0xc1a4);
    c1a8 = *(u32 *)((char *)gd + 0xc1a8);
    dblstep = ((u32)w0c + w0e + w0a) * 3 + 12;
    bitwalk = c1a0v + dblstep * 2 + w12 + (u32)fh;
    bytwalk = bitwalk + w10;

    if (w0c)
        DoubleDecodeDBook((u8 *)(c1a4 + dblstep * 2
                                 + (3 * (u32)w0a + 12) * 2 + (u32)fh),
                          (u16 *)((char *)state + 0x2044), 0,
                          (u16)flagb, gd);
    DoubleDecodeDBook((u8 *)(c1a4 + w12 + 0x18 + (u32)fh),
                      (u16 *)((char *)state + 0x44), 0, (u16)flagb, gd);
    *(u32 *)((char *)state + 0xc044) = (u32)((char *)state + 0x44);
    DoubleDecodeDBook((u8 *)(c1a4
                             + ((3 * ((u32)w0c + w0a) + 12) * 2)
                             + w12 + (u32)fh),
                      (u16 *)((char *)state + 0x4044), 1, (u16)flagb, gd);

    total = ((*(u32 *)((char *)state + 0x2c)
              + *(u32 *)((char *)gd + 0xc19c)) * w142
             + *(u32 *)((char *)state + 0x28)) * 2;
    for (iter = 0; iter < 0x2000; iter++)
        ((u32 *)c1a8)[iter] = 0;

    wbase = *(u32 *)((char *)gd + 0xc14e);
    t = (u32)*(u16 *)((char *)wbase + 4) << 9;
    shift = w142;
    if (t)
        do {
            t >>= 1;
            shift++;
        } while (t);
    SetVESABank((u16)(total >> (shift & 0x1f)));

    w144 = *(u16 *)((char *)gd + 0xc144);
    lim = (w144 < *(u32 *)((char *)state + 0x24))
          ? w144 : *(u32 *)((char *)state + 0x24);
    rowidx = 0;
    bitcnt = 0;
    if (lim != 0) {
        do {
            if (w14 <= rowidx)
                *(u32 *)((char *)state + 0xc044) =
                    (u32)((char *)state + 0x2044);
            wbase = *(u32 *)((char *)gd + 0xc14e);
            prod = (u32)*(u16 *)((char *)wbase + 4) * (u16)junkw;
            esi = ((w142 - (prod << 6)) << 4) + total;
            if (esi > (*(u16 *)((char *)wbase + 6) << 10)) {
                flagv = 1;
                esi = c1a8;
            } else {
                esi = total + ((0x280 - prod) << 10);
            }

            /* bitstream fill of the 74-dword mask; t counts bytes,+4 */
            t = 0;
            while (t < *(u32 *)((char *)state + 0x20)) {
                if (!bitcnt) {
                    bitcnt = 0x80000000;
                    curbits = *(u32 *)bitwalk;
                    bitwalk += 4;
                }
                if (curbits & bitcnt) {
                    ((u32 *)mask)[(u16)(t >> 2)] = 0xffffffff;
                    bitcnt >>= 1;
                    if (!bitcnt) {
                        bitcnt = 0x80000000;
                        curbits = *(u32 *)bitwalk;
                        bitwalk += 4;
                    }
                    if (curbits & bitcnt) {
                        CopyDDB15(
                            (void *)(*(u32 *)((char *)state + 0xc044)),
                            (void *)esi, (u8 *)bytwalk, w142 * 4 - 4);
                        bytwalk += 4;
                    } else {
                        CopyDSB15(
                            (void *)((char *)state + 0x4044
                                     + (u32)*(u8 *)bytwalk * 32),
                            (void *)esi, w142 * 4 - 12);
                        bytwalk += 1;
                    }
                } else {
                    ((u32 *)mask)[(u16)(t >> 2)] = 0;
                }
                esi += 0x10;
                bitcnt >>= 1;
                t += 4;
            }

            if (flagv) {
                wbase = *(u32 *)((char *)gd + 0xc14e);
                prod = (u32)*(u16 *)((char *)wbase + 4) * (u16)junkw;
                edi16 = (u16)((((prod
                                 + *(u16 *)((char *)wbase + 6)) << 10)
                               - total) >> 2);
                bp16 = w142 * 4 - edi16;
                y16 = (u16)(total >> (shift & 0x1f));
                res = SetVESABank(y16);
                hword = (u16)*(u32 *)((char *)state + 0x20);
                esi = c1a8;
                acc = 0;
                prevdx = 0;
                dst = total + ((0x280 - prod) << 10);
                dy = w142 - hword;

                if (edi16) {
                    if ((s16)edi16 > 0) {
                        do {
                            if ((s16)edi16 >= (s16)hword) {
                                dx = hword;
                                res = dy;
                            } else {
                                res = 0;
                                dx = edi16;
                            }
                            bidx = 0;
                            t = res + dx;
                            edi16 -= t;
                            prevdx = dx;
                            acc += t;
                            if ((s16)dx > 0) {
                                do {
                                    if (((u8 *)mask)[bidx] != 0)
                                        *(u32 *)dst = *(u32 *)esi;
                                    dst += 4;
                                    esi += 4;
                                    dx--;
                                    bidx++;
                                } while (dx != 0);
                            }
                            dst += (s16)res * 4;
                            esi += (s16)res * 4;
                        } while ((s16)edi16 > 0);
                    }
                    res = SetVESABank(y16 + 1);
                }

                if (bp16) {
                    wbase = *(u32 *)((char *)gd + 0xc14e);
                    prod = (u32)*(u16 *)((char *)wbase + 4) * (u16)junkw;
                    dst = total + (((0x280 - prod) << 8) + (s16)acc) * 4;
                    if (res == 0) {
                        /* phase 2a: completes the hword row; mask byte
                           index CONTINUES from Y1's last span (FA keeps
                           bx without resetting it here) */
                        dx = hword - prevdx;
                        bp16 -= dy + dx;
                        if ((s16)dx > 0) {
                            do {
                                if (((u8 *)mask)[bidx] != 0)
                                    *(u32 *)dst = *(u32 *)esi;
                                dst += 4;
                                esi += 4;
                                dx--;
                                bidx++;
                            } while (dx != 0);
                        }
                        dst += (s16)dy * 4;
                        esi += (s16)dy * 4;
                    } else {
                        /* phase 2b: FA adds the leftover (post-Y1) edi16 */
                        bp16 += edi16;
                    }
                    while ((s16)bp16 > 0) {
                        if ((s16)bp16 >= (s16)hword) {
                            dx = hword;
                            res = dy;
                        } else {
                            res = 0;
                            dx = bp16;
                        }
                        bidx = 0;
                        bp16 -= res + dx;
                        if ((s16)dx > 0) {
                            do {
                                if (((u8 *)mask)[bidx] != 0)
                                    *(u32 *)dst = *(u32 *)esi;
                                dst += 4;
                                esi += 4;
                                dx--;
                                bidx++;
                            } while (dx != 0);
                        }
                        dst += (s16)res * 4;
                        esi += (s16)res * 4;
                    }
                }
                flagv = 0;
            }

            total += (u32)w142 << 4;
            rowidx += 4;
        } while (rowidx < lim);
    }
    (void)j16;      /* FA pad slot unused here */
}