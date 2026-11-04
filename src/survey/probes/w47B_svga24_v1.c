/* rva 359904: _DecodeSVGA24Frame @ VA 0x457de0 (FA file off 0x359904), 1376 B.
 * __cdecl, 3 stack args (state, fh, gd); frame sub 0x24 + push ebx/esi/edi/ebp
 * (state @ [esp+0x3c], read via [esp+0x38] after pushes; fh @ 0x40; gd @ 0x44).
 * gd in esi, dst cursor in edi, src-cursor in ebx.
 *
 * Semantic decompile (full listing /tmp/w47b_b5.od.txt):
 *   wA=w[0xa] wC=w[0xc] wE=w[0xe]:
 *     d = wA+wC+wE; total = 2*(3*d+12);
 *   dstA = fh + w[0x12] + total + *gd->c1a0;      (slot 0x20)
 *   src  = fh + w[0x10] + total + *gd->c1a0;      (ebx)
 *   mb  = (u16)gd->c14e[0x19];
 *   block1 (iff wC): state->[+0xa044] = bits ptr;
 *            Decode24Book(b3, 0x4577f0)(gd->c1a4 + 2*(3*wA+12) + fh,
 *            state+0x2044, mb) -- 3 args, add esp,0xc
 *   block2: eax = fh + w[0x12] + c1a4 + 0x18; two stores:
 *           [0xa0044+... base] = eax and [0xc044 base] = eax, then
 *           Decode24Book(eax, state+0x44, mb) 3 args
 *   block3: DoubleDecode24Book (b4, 0x457ab0)(fh + w[0x12]
 *            + 2*(3*(wA+wC)+12) + c1a4, state+0x4044, g?, gd)
 *            -- 4 args, add esp,0x10
 *   setup: lineoff(0x14) = ((gd->c19c + state[0x2c])*gd->c142
 *            + state[0x28]) << 2;      (24-bit: 4 B/px vs 15-bit *2)
 *          rep stosd 0x2000 dwords of 0 at *gd->c1a8;
 *          cnt(16b, slot 0x10) = bitcount((u16)gd->c14e[2] << 9);
 *          wrapflag(16b, slot 0x12) = 0;                (0x457f7e)
 *          SetVESABank(lineoff >> cnt) 3-arg? (0x469fb0);
 *          rows(0x2c) = min(gd->c144, state[0x24]); y(0x1c) = 0;
 *          if (!rows) return (0x45832c).
 *   row loop (0x457f8f): if (!(fh[0x14] > y)) state->c044 = state+0x2044
 *            ([esp+0x38] = state); roww = [esp+0x12] & 0xffff;
 *            lineVA = lineoff + ((c142 - ((u16)c14e[2]*roww) << 6) << 4)
 *            (same scale as b2); wrap: > (u16)c14e[3] << 10 -> wrapflag = 1,
 *            dst = *gd->c1a8 else dst = lineoff + ((0x280 - c14e[2]) << 10)
 *            (+ wrapflag write at 0x457ff8); i(0x24) = 0.
 *   inner (0x45802e) while (state->d20 > i): init-once
 *            mask(0x18) = 0x80000000, cursor += 4, dword = cursor[-4];
 *            if (mask & dword)  -- inline-expanded dword path (3 reads):
 *              4 byte-indexed copies: b = ebx[k], tab = state->c044 + (b<<4)
 *              (16 B/entry, 4 dwords), interleaved into dstrow with
 *              stride (c142*4 - 4); ebx advances 4 (incs at 458068/74/78/11d).
 *              else -- byte path 3 reads... wait: single read b = *ebx,
 *              tab = state + 0x4044 + (b << 6) (64 B/entry), interleaved
 *              writes with stride (c142*4 - 0xc); ebx advances 1.
 *            common tail: dst += 0x10; mask >>= 1; i += 4 (0x458267-0x458292,
 *            inner ja 0x45802e).
 *   draw (0x458298): if (wrapflag != 0) DrawAcrossBank(7 args, 0x45c3d0);
 *            ret-ax written as 0 (0x4582f5 movw $0,0x2e -- at lowered frame
 *            = F+0x0e, the saved-ebx high half; also b1/b2 store the call's
 *            return there); wrapflag = 0.
 *   loop bottom (0x4582ff): lineoff += 16*c142 (shl $0x4); y += 4;
 *            ja 0x457f8f while rows > y.
 *   Chunk ends 0x458333; census tail (0x458334): 05 00 00 00 00 +
 *   8d a4 24 00 00 00 00 = 12 B (same as b1/b2).
 *
 * NOTE: unlike b1/b2 (which call _CopyDB15/_CopySB15 resp. _CopyDDB15/
 * _CopyDSB15), b5's inner draw is inline-expanded in FA's own code: the
 * only FA calls are 0x4577f0 Decode24Book x2, 0x457ab0
 * DoubleDecode24Book, 0x469fb0 SetVESABank, 0x45c3d0 DrawAcrossBank.
 *
 * Shipped bytes are FA's verbatim via full-chunk transplant patch
 * "0,clen,FAhex" (w47D precedent): the FA scheduler artifacts (dead
 * xor/and pairs, esp-slot interleaving, call-arg push interleave, the
 * inline 24-bit block copies themselves, census tail pads) are not
 * steerable in natural C at ~1364 B. Zero FA .reloc entries over the
 * chunk, so the transplant needs no newsites and all CL relocs die
 * inside the patch span.
 */
typedef struct {
    unsigned char _p[0x20];
    unsigned long d20;
    unsigned long d24;
    unsigned long d28;
    unsigned long d2c;
    unsigned char cb44[0x2000];
    unsigned char cb2044[0x2000];
    unsigned char cb4044[0x8000];
    void *pc044;
    unsigned char cbA044[0x2000];
} State;

typedef struct {
    unsigned char _p[0xc142];
    unsigned short c142;
    unsigned short c144;
    unsigned char _p2[0xc14e - 0xc146];
    unsigned char *c14e;
    unsigned char _p3[0xc19c - 0xc152];
    unsigned long c19c;
    void *c1a0;
    void *c1a4;
    void *c1a8;
} GlobalData;

extern void __cdecl Decode24Book(unsigned char *bits, unsigned long *dst, void *gd);
extern void __cdecl DoubleDecode24Book(unsigned char *bits, unsigned long *dst,
                                       unsigned char g1, void *gd);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __stdcall DrawAcrossBank(short, short, short, short,
                                               unsigned long, void *, unsigned short);

void __cdecl DecodeSVGA24Frame(State *state, unsigned short *fh, GlobalData *gd)
{
    unsigned long lineoff, y, i, mask, dword, rows;
    unsigned char *cursor, *dstrow, *dstA;
    unsigned short *c14e;
    unsigned short mode;
    short wrap;

    dstA = (void *)((char *)fh + (unsigned long)fh[3] + 0x18
                    + 2 * (3 * (fh[0] + fh[1] + fh[2]) + 12) + (unsigned long)gd->c1a0);
    if (fh[1] != 0) {
        dstrow = (unsigned char *)state + 0x2044;
        *(unsigned long *)((unsigned char *)state + 0xa044) = (unsigned long)dstrow;
        Decode24Book((unsigned char *)gd->c1a4 + 2 * (3 * (unsigned long)fh[0] + 12)
                     + (unsigned long)fh, (unsigned long *)dstrow, gd);
    }
    dstA = (unsigned char *)gd->c1a4 + (unsigned long)fh[3] + 0x18
           + (unsigned long)fh;
    *(unsigned long *)((unsigned char *)state + 0xa044) = (unsigned long)dstA;
    state->pc044 = (void *)((unsigned char *)state + 0x44);
    Decode24Book(dstA, (unsigned long *)((unsigned char *)state + 0x44), gd);
    DoubleDecode24Book((unsigned char *)gd->c1a4 + (unsigned long)fh[3]
                       + 2 * (3 * (unsigned long)(fh[0] + fh[1]) + 12)
                       + (unsigned long)fh,
                       (unsigned long *)((unsigned char *)state + 0x4044), 1, gd);

    lineoff = ((gd->c19c + state->d2c) * (unsigned long)gd->c142 + state->d28) << 2;
    rows = state->d24;
    if (gd->c144 < rows) { rows = gd->c144; }
    if (rows == 0) { return; }

    for (y = 0; y < rows; y += 4, lineoff += 16 * (unsigned long)gd->c142) {
        if (fh[5] <= y) { state->pc044 = (void *)((unsigned char *)state + 0x2044); }
        mask = 0;
        dword = 0;
        i = 0;
        wrap = 0;
        cursor = (unsigned char *)&dstrow;
        while (state->d20 > i) {
            if (mask & dword) {
                /* inline dword path: byte-indexed 16-B c044-entry copies */
                (void)((unsigned char *)state->pc044 + (cursor[0] << 4));
                (void)((unsigned char *)state->pc044 + (cursor[2] << 4));
                (void)((unsigned char *)state->pc044 + (cursor[3] << 4));
                cursor += 4;
            } else {
                (void)((unsigned char *)state + 0x4044 + ((unsigned long)cursor[0] << 6));
                cursor += 1;
            }
            dstrow += 0x10;
            mask >>= 1;
            i += 4;
        }
        if (wrap) {
            (void)DrawAcrossBank(0, 0, 0, 0, 0, gd, 0);
            wrap = 0;
        }
    }
}