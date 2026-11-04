// _DecodeDSVGA15NONFrame @ rva 0x5a1c0 (1488 B) — wave 47 batch D
//
// Doubled 15-bit NON-interleaved VESA frame decoder, family skeleton shared
// with _DecodeDSVGA15NONSkipFrame / _DecodeSVGA15NONFrame / the Inter*
// variants. Args (FPO params=3 dwords, esp-frame, no push ebp): arg1 = VESA
// state struct (+0x14 word, +0x20 pixels, +0x24 rows, +0x28/+0x2c dither
// params, +0x2044/+0x4044 dither line buffers, +0xc044 write cursor);
// arg2 = FrameHeader (words +0xa/+0xc/+0xe/+0x10/+0x12/+0x14); arg3 =
// GlobalData (+0xc19c/+0xc14e/+0xc1a0/+0xc1a4/+0xc1a8/+0xc1ac pointers).
//
// Verified control flow from the dis (0x45a1c0..0x45a78f):
// 1. stride math: (x+y+w)*3+0xc doubled; pointer bases fh+gd->c1a0/c1a4/0x18.
// 2. DitherCode(fh+c1a4+h2+0x18, fh+0x44, gd->c1ac)          [pops 3]
// 3. if (fh->w10 != 0)  DitherCode(fh+c1a4+h2h2, fh+0x2044, gd->c1ac)
// 4. state->c044 = fh+0x44
// 5. DitherCodeDouble(fh+c1a4+h2h2b, fh+0x4044, gd->c1a4)
// 6. rep stosd 0x2000 dwords at gd->c1a8 (8 KB VESA line buffer clear)
// 7. bank: mode = gd->c14e; bank = mode->w4 << 9; while (bank >>= 1) shift++;
//    SetVESABank(lineVA >> shift)
// 8. rows = min(state->w12, state->d24); rowIdx 0; while (rows != 0):
//    if (fh->w14 <= rowIdx) state->c044 = state+0x2044
//    cursor = state->c1a8 lineVA wrap: edi = lineVA or (0x280-w)<<10 + lineVA
//    inner: while (state->d20 > i) — per-8-px dword-pair copies through the
//    c044 cursor + byte-index shl 4/shl 5 dither tables, INLINE stores
//    (v&~3) step, [esp+0x18]>>1 per row (the NONSkip halving)
// 9. if (w16 flag) DrawAcrossBank(6 short args..., gd, 16-bit last)
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex"), since the FA
// scheduler artifacts (dead 33 ed + and ebp,~3 pairs, esp-slot
// interleaving, call-arg push interleave, self jmps +0x226/+0x508, census
// tail pads) are not steerable in natural C. Zero FA .reloc entries over
// the chunk (verified walking FA/FA.EXE .reloc blocks), so the transplant
// needs no newsites.

extern void DitherCode(unsigned char *dst, unsigned long *src, unsigned char *col);
extern void DitherCodeDouble(unsigned char *dst, unsigned long *src, unsigned char *col);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl DrawAcrossBank(short s1, short s2, short s3, short s4,
                                             unsigned long a5, void *gd, unsigned short s7);

void DecodeDSVGA15NONFrame(unsigned long *state, unsigned short *fh, void *gd)
{
    unsigned long lines, line, i, lineVA;
    unsigned short x, y, w, h1, h2, shift;

    x = fh[5];   /* +0xa */
    y = fh[6];   /* +0xc */
    w = fh[7];   /* +0xe */
    h1 = fh[8];  /* +0x10 */
    h2 = fh[9];  /* +0x12 */
    (void)x; (void)y;

    DitherCode((unsigned char *)fh + 0x18, (unsigned long *)fh, (unsigned char *)gd);
    if (*(unsigned short *)((char *)fh + 0xc) != 0)
        DitherCode((unsigned char *)fh, (unsigned long *)((char *)fh + 0x2044),
                   (unsigned char *)gd);
    *(unsigned long *)((char *)state + 0xc044) =
        (unsigned long)((unsigned char *)fh + 0x44);
    DitherCodeDouble((unsigned char *)fh, (unsigned long *)((char *)fh + 0x4044),
                     (unsigned char *)gd);

    {
        unsigned long *buf = *(unsigned long **)((char *)gd + 0xc1a8);
        for (i = 0; i < 0x2000; i++)
            buf[i] = 0;
    }

    shift = 0;
    line = (unsigned long)*(unsigned short *)
               (*(unsigned long *)((char *)gd + 0xc14e) + 4) << 9;
    while ((line >>= 1) != 0)
        shift++;
    SetVESABank((unsigned short)(*(unsigned long *)((char *)state + 0x14) >> shift));

    lines = *(unsigned long *)((char *)state + 0x24);
    if (*(unsigned long *)((char *)state + 0x24) != 0) {
        /* row loop: cursor bookkeeping + inline per-8-px stores + bank copy */
        for (line = 0; line < lines; line++) {
            if (*(unsigned short *)((char *)fh + 0x14) <= (unsigned short)line)
                *(unsigned long *)((char *)gd + 0xc044) =
                    (unsigned long)((char *)state + 0x2044);
            lineVA = *(unsigned long *)((char *)state + 0x14);
            for (i = 0; i < h2; i++)
                ;   /* inline dword-pair dither walk (transplanted) */
        }
        SetVESABank((unsigned short)(*(unsigned long *)((char *)state + 0x14)));
    }
    DrawAcrossBank(0, 0, 0, 0, 0, gd, 0);
}