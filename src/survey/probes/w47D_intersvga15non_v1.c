// _DecodeInterSVGA15NONFrame @ rva 0x5aff0 (1200 B) — wave 47 batch D
//
// Interleaved sibling of _DecodeSVGA15NONFrame (0x5ac40). FPO params=3
// dwords, locals=88 dwords (the 0x128-B row mask at esp+0x30, built by the
// rolling ebx=0x80000000 mask loop storing 0xff/0x00 bytes), esp-frame
// (sub esp,0x160), cbProlog=24, no SEH. arg1 = VESA state struct; arg2 =
// FrameHeader (words +0xa/+0xc/+0xe/+0x12...); arg3 = GlobalData
// (+0xc1a0/+0xc1a4/+0xc1a8/+0xc1ac pointers).
//
// Verified calls (dis 0x45aff0..0x45b44f):
//   DitherCodeSingle x2, DitherCode, SetVESABank, _CopyDB8, _CopySB8,
//   DrawAcrossBankInter (8th arg = the local mask buffer, unsigned char*).
// Tail pad 7 B (8da42400000000).
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex") — the rolling
// mask construction in esp slots, the 8-px CopyDB8/CopySB8 scheduling and
// census tail pad are not steerable in natural C. Zero FA .reloc entries
// over the chunk (verified walking FA/FA.EXE .reloc blocks), so the
// transplant needs no newsites.

extern void DitherCodeSingle(unsigned char *dst, unsigned short *src, unsigned char *col);
extern void DitherCode(unsigned char *dst, unsigned long *src, unsigned char *col);
extern void CopyDB8(void);
extern void CopySB8(void);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl DrawAcrossBankInter(short s1, short s2, short s3, short s4,
                                                  unsigned long a5, void *gd,
                                                  unsigned short s7, unsigned char *mask);

void DecodeInterSVGA15NONFrame(unsigned long *state, unsigned short *fh, void *gd)
{
    unsigned char mask[0x128];
    unsigned long rows, line, i, m;

    (void)fh;
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

    /* rolling mask: ebx starts 0x80000000, byte store 0xff then 0x00 per bit */
    for (m = 0; m < 0x100; m++)
        mask[m] = (unsigned char)((m & 1) ? 0x00 : 0xff);

    rows = *(unsigned long *)((char *)state + 0x24);
    for (line = 0; line < rows; line++) {
        if (*(unsigned short *)((char *)fh + 0x14) <= (unsigned short)line)
            *(unsigned long *)((char *)gd + 0xc044) =
                (unsigned long)((char *)state + 0x2044);
        CopyDB8();
        CopySB8();
    }
    DrawAcrossBankInter(0, 0, 0, 0, 0, gd, 0, mask);
}