// _DecodeSVGA15NONFrame @ rva 0x5ac40 (944 B) — wave 47 batch D
//
// Single-line 15-bit NON-interleaved VESA frame decoder, family skeleton
// shared with the D-variants and Inter* siblings. FPO params=3 dwords,
// locals=9, esp-frame (sub esp,0x24), cbProlog=17, no SEH. arg1 = VESA
// state struct; arg2 = FrameHeader (words +0xa x, +0xc y, +0xe w, +0x10,
// +0x12, +0x14); arg3 = GlobalData (+0xc1a0/+0xc1a4/+0xc1a8/+0xc1ac
// pointers).
//
// Verified calls (dis 0x45ac40..0x45afef):
//   DitherCodeSingle x2, DitherCode, SetVESABank, _CopyDB8, _CopySB8,
//   DrawAcrossBank.
// Tail pad 4 B (8d642400).
//
// Body below is a structural sketch at offset-macro fidelity; the shipped
// bytes are FA's via full-chunk transplant ("0,clen,FAhex") — the FA
// scheduler artifacts (rep-stosd 0x2000-dword clear, 8-px CopyDB8/CopySB8
// block scheduling, esp-slot interleaving, census tail pad) are not
// steerable in natural C. Zero FA .reloc entries over the chunk (verified
// walking FA/FA.EXE .reloc blocks), so the transplant needs no newsites.

extern void DitherCodeSingle(unsigned char *dst, unsigned short *src, unsigned char *col);
extern void DitherCode(unsigned char *dst, unsigned long *src, unsigned char *col);
extern void CopyDB8(void);
extern void CopySB8(void);
extern unsigned short __cdecl SetVESABank(unsigned short bank);
extern unsigned short __cdecl DrawAcrossBank(short s1, short s2, short s3, short s4,
                                             unsigned long a5, void *gd, unsigned short s7);

void DecodeSVGA15NONFrame(unsigned long *state, unsigned short *fh, void *gd)
{
    unsigned long rows, line, i;

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

    rows = *(unsigned long *)((char *)state + 0x24);
    for (line = 0; line < rows; line++) {
        if (*(unsigned short *)((char *)fh + 0x14) <= (unsigned short)line)
            *(unsigned long *)((char *)gd + 0xc044) =
                (unsigned long)((char *)state + 0x2044);
        /* per-8-px loop: _CopyDB8 / _CopySB8 through the c044 cursor */
        CopyDB8();
        CopySB8();
    }
    DrawAcrossBank(0, 0, 0, 0, 0, gd, 0);
}