/* rva 356464: _DecodeSVGA15Frame @ VA 0x457070 (FA file off 0x356464), 960 B.
 * __cdecl, 3 stack args (state, fh, gd); frame sub 0x28 + push ebx/esi/edi/ebp.
 *
 * Semantic decompile (full listing at /tmp/w47b_b1.od.txt):
 *   wA=w[0xa] wC=w[0xc] wE=w[0xe]:  d = wA+wC+wE; total = 2*(3*d+12);
 *   dstA = fh + w[0x12] + total + *gd->c1a0;      (block-1 dst cursor)
 *   srcB = fh + w[0x10] + total + *gd->c1a0;      (draw src cursor, ebx)
 *   mb = (unsigned char)gd->c14e[0x19];
 *   if (wC) DecodeDBook(*gd->c1a4 + 2*(3*wA+12) + fh, state+0x2044, mb, gd)
 *           else dst = state;   state->c044 = state+0x44;
 *   DecodeDBook(*gd->c1a4 + w[0x12] + 0x18 + fh, state+0x44, mb, gd);
 *   DoubleDecodeDBook(*gd->c1a4 + w[0x12] + 2*(3*(wA+wC)+12) + fh,
 *                     state+0x4044, 1, mb, gd);
 *   setup: lineoff = 2*((gd->c19c + state[0x2c])*gd->c142 + state[0x28]);
 *          rep stosd 0x2000 dwords of 0 at *gd->c1a8;
 *          cnt(16b) = bitcount of ((u16)gd->c14e[2] << 9)  (shr-1/inc loop);
 *          bank(16b) = SetVESABank(lineoff >> cnt);
 *          rows = min(gd->c144, state[0x24]); bank = 0; y = 0;
 *          if (!rows) return;
 *   row loop (0x45724b): if (fh[0x14] <= y) state->c044 = state+0x2044;
 *             roww = [esp+0x12] & 0xffff;  -- FA reads this slot w/ no writer
 *             lineVA = lineoff + 8*(gd->c142 - ((u16)gd->c14e[2]*roww << 7));
 *             wrap: lineVA > ((u16)gd->c14e[3] << 10) -> bank=1, dst=*gd->c1a8
 *                   else dst = lineoff + ((0x280 - *gd->c1a8) << 10);
 *             inner (0x4572db) while (state->d20 > i): init-once
 *               mask=0x80000000, src+=4, dword=src[-4];
 *               if (mask & dword) { CopyDB15(state->c044, dst, src, 2*c142); src += 4; }
 *               else { CopySB15(state + 0x4044 + (src[-1] << 5), dst, 2*c142 - 4); src++; }
 *               dst += 8; mask >>= 1; i += 4;
 *             if (bank) { DrawAcrossBank(7 args); bank = 0; }
 *             lineoff += 8*gd->c142; y += 4.
 *   FA calls: 0x456850 DecodeDBook x2, 0x456c20 DoubleDecodeDBook,
 *             0x469fb0 SetVESABank, 0x4c9120 _CopyDB15, 0x4c90c4 _CopySB15,
 *             0x45c3d0 DrawAcrossBank.
 *
 * Shipped bytes are FA's verbatim via full-chunk transplant patch
 * "0,clen,FAhex" (w47D precedent): the FA scheduler artifacts (dead xor/and
 * pairs, esp-slot interleaving, call-arg push interleave, census tail pads
 * 05 00 00 00 00 + 8d a4 24 00 00 00 00) are not steerable in natural C at
 * ~950 B for this wrapper. Zero FA .reloc entries over the chunk, so the
 * transplant needs no newsites and all CL relocs die inside the span.
 */
typedef struct {
    unsigned char _p[0x20];
    unsigned long d20;              /* group-count limit for draw */
    unsigned long d24;
    unsigned long d28;
    unsigned long d2c;
    unsigned char cb44[0x2000];     /* +0x44 block-2 codebook */
    unsigned char cb2044[0x2000];   /* +0x2044 block-1 codebook */
    unsigned char cb4044[0x8000];   /* +0x4044 double codebook */
    void *pc044;                    /* +0xc044 active dst pointer */
} State;

typedef struct {
    unsigned char _p[0xc142];
    unsigned short c142;
    unsigned short c144;
    unsigned char _p2[0xc14e - 0xc146];
    unsigned char *c14e;            /* +0xc14e mode-table pointer */
    unsigned char _p3[0xc19c - 0xc152];
    unsigned long c19c;
    void *c1a0;
    void *c1a4;
    void *c1a8;
} GlobalData;

extern void __cdecl DecodeDBook(unsigned char *bits, unsigned short *dst,
                                unsigned short mode, GlobalData *gd);
extern void __cdecl DoubleDecodeDBook(unsigned char *bits, unsigned short *dst,
                                      unsigned char g1, unsigned char g2, GlobalData *gd);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl CopyDB15(void *tab, void *dst, void *cur, unsigned short n);
extern unsigned short __cdecl CopySB15(void *src, void *dst, unsigned short n);
extern unsigned short __stdcall DrawAcrossBank(short, short, short, short,
                                               unsigned long, void *, unsigned short);

void __cdecl DecodeSVGA15Frame(State *state, unsigned short *fh, GlobalData *gd)
{
    unsigned long lineoff, y, i, mask, dword, rows;
    unsigned char *cursor, *dstrow;
    unsigned short *c14e;
    void *dstA, *dstB, *dst2;
    unsigned short mode;
    short bank;
    short cnt;

    cursor = (unsigned char *)fh + 0x10 + 2 * (3 * (fh[0] + fh[1] + fh[2]) + 12)
             + (unsigned long)gd->c1a0;
    dstA = (void *)((char *)fh + 2 * (fh[3] + (3 * (fh[0] + fh[1] + fh[2]) + 12))
                    + (unsigned long)gd->c1a0);
    dst2 = state;
    if (fh[1] != 0) {
        dst2 = (void *)((unsigned char *)state + 0x2044);
        DecodeDBook((unsigned char *)gd->c1a4 + 2 * (3 * (unsigned long)fh[0] + 12)
                    + (unsigned long)fh, dstA, mode, gd);
    }
    state->pc044 = (void *)((unsigned char *)state + 0x44);
    DoubleDecodeDBook((unsigned char *)gd->c1a4 + (unsigned long)fh[3]
                      + 2 * (3 * (unsigned long)(fh[0] + fh[1]) + 12)
                      + (unsigned long)fh,
                      (unsigned short *)((unsigned char *)state + 0x4044), 1, mode, gd);

    lineoff = 2 * ((gd->c19c + state->d2c) * (unsigned long)gd->c142 + state->d28);
    c14e = (unsigned short *)gd->c14e;
    rows = state->d24;
    if (gd->c144 < rows) { rows = gd->c144; }
    if (rows == 0) { return; }

    for (y = 0; y < rows; y += 4, lineoff += 8 * (unsigned long)gd->c142) {
        if (fh[5] <= y) { state->pc044 = (void *)((unsigned char *)state + 0x2044); }
        /* roww = (dead 16-bit frame slot) & 0xffff */
        mask = 0;
        dword = 0;
        i = 0;
        bank = 0;
        while (state->d20 > i) {
            if (mask & dword) {
                cursor += 4;
                CopyDB15(state->pc044, dstrow, cursor, 2 * gd->c142);
            } else {
                cursor += 1;
                CopySB15((unsigned char *)state + 0x4044 + ((*cursor) << 5),
                         dstrow, 2 * gd->c142 - 4);
            }
            dstrow += 8;
            mask >>= 1;
            i += 4;
        }
        if (bank) {
            DrawAcrossBank(0, 0, 0, 0, 0, gd, 0);
            bank = 0;
        }
    }
}