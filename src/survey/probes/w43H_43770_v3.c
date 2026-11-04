// _GRAPHICMakeAdder@24 @ rva 0x43770 (128 B; FPO locals 0; code 114 B +
// 14 B lea-pad).  stdcall 6 args (ret 0x18).  V3: count declared before p
// (FA: eax=ptr, ecx=count), m[3] |= 1 array spelling for the single-instr
// RMW, FA store order 4b/4a/4d/4e/4f/50.
extern char w43H_graphics[];    /* map =_graphics */
extern char w43H_noMixLeft[];   /* map =?noMixLeft@@3UMODSPEC@@A */
extern long __fastcall w43H_gAdd(long what);  /* map =@w43H_gAdd@4=$FA$_t_443280 */

void __stdcall w43H_43770v3(unsigned char *m, unsigned char a2,
    unsigned long a3, unsigned char a4, unsigned char a5, unsigned char a6)
{
    if (m) {
        unsigned short mask = 0x100;
        long count = 0;
        char *p = w43H_graphics;
        long r;
        do {
            if (*(unsigned short *)(p + 2) & mask)
                count++;
            p += 0x66;
        } while (p < w43H_noMixLeft);
        if (count >= 6) {
            r = w43H_gAdd(1);
            if (r)
                *(unsigned short *)((char *)r + 4) = 0xffff;
        }
        m[3] |= 1;
        *(unsigned short *)((char *)m + 0x4b) = (unsigned short)a3;
        *(unsigned char *)((char *)m + 0x4a) = a2;
        *(unsigned char *)((char *)m + 0x4d) = a4;
        *(unsigned char *)((char *)m + 0x4e) = a5;
        *(unsigned char *)((char *)m + 0x4f) = a6;
        *(unsigned long *)((char *)m + 0x50) = 0;
    }
}