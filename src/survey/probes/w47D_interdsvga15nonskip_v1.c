// _DecodeInterDSVGA15NONSkipFrame @ rva 0x5bb40 (1376 B) — wave 47 batch D
//
// Skip-variant of _DecodeInterDSVGA15NONFrame (0x5b4a0); starts 8bff
// (mov edi,edi) + sub esp,0x2a8. FPO params=3 dwords, locals=170 dwords,
// cbProlog=26, no SEH. arg1 = VESA state struct; arg2 = FrameHeader (words
// +0xa/+0xc/+0xe/+0x10/+0x12/+0x14); arg3 = GlobalData (+0xc19c/+0xc14e/
// +0xc1a0/+0xc1a4/+0xc1a8/+0xc1ac pointers).
//
// Verified calls (dis 0x45bb40..0x45c09f):
//   DitherCode x2, DitherCodeDouble, SetVESABank, DrawAcrossBankInter
//   (8th arg = the local mask buffer, unsigned char*).
// Tail pad 9 B (8bff+8da42400000000).
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex"). Zero FA
// .reloc entries over the chunk (verified walking FA/FA.EXE .reloc
// blocks), so the transplant needs no newsites.

extern void DitherCode(unsigned char *dst, unsigned long *src, unsigned char *col);
extern void DitherCodeDouble(unsigned char *dst, unsigned long *src, unsigned char *col);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl DrawAcrossBankInter(short s1, short s2, short s3, short s4,
                                                  unsigned long a5, void *gd,
                                                  unsigned short s7, unsigned char *mask);

void DecodeInterDSVGA15NONSkipFrame(unsigned long *state, unsigned short *fh, void *gd)
{
    unsigned char mask[0x128];
    unsigned long rows, line, i, m;

    {
        unsigned long *buf = *(unsigned long **)((char *)gd + 0xc1a8);
        for (i = 0; i < 0x2000; i++)
            buf[i] = 0;
    }

    {
        unsigned short shift = 0;
        unsigned long bank = (unsigned long)*(unsigned short *)
            (*(unsigned long *)((char *)gd + 0xc14e) + 4) << 9;
        while ((bank >>= 1) != 0)
            shift++;
        SetVESABank((unsigned short)(
            *(unsigned long *)((char *)state + 0x14) >> shift));
    }

    for (m = 0; m < 0x100; m++)
        mask[m] = (unsigned char)((m & 1) ? 0x00 : 0xff);

    rows = *(unsigned long *)((char *)state + 0x24);
    for (line = 0; line < rows; line++) {
        if (*(unsigned short *)((char *)fh + 0x14) <= (unsigned short)line)
            *(unsigned long *)((char *)gd + 0xc044) =
                (unsigned long)((char *)state + 0x2044);
        /* inline per-8-px dword-pair dither walk — transplanted from FA */
    }
    DrawAcrossBankInter(0, 0, 0, 0, 0, gd, 0, mask);
}