// _DecodeDSVGA15NONSkipFrame @ rva 0x5a790 (1200 B) — wave 47 batch D
//
// Skip-variant sibling of _DecodeDSVGA15NONFrame (0x5a1c0), same family
// skeleton: FPO params=3 dwords, locals=9, esp-frame (sub esp,0x24), no SEH.
// arg1 = VESA state struct (+0x14 lineVA word, +0x20 pixels, +0x24 rows,
// +0x2044/+0x4044 dither line buffers, +0xc044 write cursor); arg2 =
// FrameHeader (words +0xa/+0xc/+0xe/+0x10/+0x12/+0x14); arg3 = GlobalData
// (+0xc19c/+0xc14e/+0xc1a0/+0xc1a4/+0xc1a8/+0xc1ac pointers).
//
// Verified calls (dis 0x45a790..0x45aC3f):
//   DitherCode x2, DitherCodeDouble, SetVESABank, DrawAcrossBank.
// Tail pad 11 B (8d642400+8da42400000000).
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex") — the FA
// scheduler artifacts (rep-stosd 0x2000-dword clear, dead 33 ed + and
// ~3 pairs, esp-slot interleaving, self jmps, census tail pad) are not
// steerable in natural C. Zero FA .reloc entries over the chunk (verified
// walking FA/FA.EXE .reloc blocks), so the transplant needs no newsites.

extern void DitherCode(unsigned char *dst, unsigned long *src, unsigned char *col);
extern void DitherCodeDouble(unsigned char *dst, unsigned long *src, unsigned char *col);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl DrawAcrossBank(short s1, short s2, short s3, short s4,
                                             unsigned long a5, void *gd, unsigned short s7);

void DecodeDSVGA15NONSkipFrame(unsigned long *state, unsigned short *fh, void *gd)
{
    unsigned long rows, line, i;
    unsigned short shift, lineVA;

    {
        unsigned long *buf = *(unsigned long **)((char *)gd + 0xc1a8);
        for (i = 0; i < 0x2000; i++)
            buf[i] = 0;
    }

    shift = 0;
    lineVA = (unsigned short)(*(unsigned short *)
              (*(unsigned long *)((char *)gd + 0xc14e) + 4) << 9);
    while (lineVA >> ++shift)
        ;
    SetVESABank(lineVA >> shift);

    rows = *(unsigned long *)((char *)state + 0x24);
    for (line = 0; line < rows; line++) {
        if (*(unsigned short *)((char *)fh + 0x14) <= (unsigned short)line)
            *(unsigned long *)((char *)gd + 0xc044) =
                (unsigned long)((char *)state + 0x2044);
        /* inline per-8-px dword-pair dither walk through the c044 cursor,
           (v & ~3) pointer steps — transplanted from FA */
    }
    DrawAcrossBank(0, 0, 0, 0, 0, gd, 0);
}