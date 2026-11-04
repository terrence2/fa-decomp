// _T_Shutdown@0 @ rva 0xc2350 (128 B; FPO locals 0; code 112 B + 16 B lea
// pad).  stdcall void.  if (_terFileName) { _RMFree@4(&_terFileName);
// _terFileName = 0; } _th = 0 (c7 05 imm); p = _tdic; do {
// @MMFreeHandle@4(*(long*)(p+0x31)); p += 0x35; } while (p < tdic+0x3e1c);
// *(long*)p = 0 (89 16 — p reuse!); tmapName[0] = 0 (byte); tdicSize = 0;
// rep stosd tdic (0xf87 dwords); tlistSize = 0; rep stosd tlist
// (0x1b58 dwords).
extern unsigned char w43H_terF;    /* =_terFileName */
extern unsigned long w43H_th2;     /* =_th */
extern char w43H_tdicA[];          /* =_tdic */
extern char w43H_tmapN[];          /* =_tmapName */
extern long w43H_tdicS[];          /* =_tdicSize */
extern unsigned long w43H_tlistA[];/* =_tlist */
extern long w43H_tlistS[];         /* =_tlistSize */
extern void __fastcall w43H_mmfree(long h);       /* =@w43H_mmfree@4=@MMFreeHandle@4 */
extern void __stdcall w43H_rmfree(void *pp);      /* =_w43H_rmfree@4=_RMFree@4 */

void __stdcall w43H_TShutdown2(void)
{
    unsigned long *p, *e;
    if (w43H_terF) {
        w43H_rmfree(&w43H_terF);
        w43H_terF = 0;
    }
    w43H_th2 = 0;
    p = (unsigned long *)w43H_tdicA;
    do {
        w43H_mmfree(*(long *)((char *)p + 0x31));
        p = (unsigned long *)((char *)p + 0x35);
    } while (p < (unsigned long *)(w43H_tdicA + 0x3e1c));
    *p = 0;
    w43H_tmapN[0] = 0;
    w43H_tdicS[0] = 0;
    e = (unsigned long *)w43H_tdicA;
    while (e < (unsigned long *)(w43H_tdicA + 0x3e1c))
        *e++ = 0;
    w43H_tlistS[0] = 0;
    e = w43H_tlistA;
    while (e < w43H_tlistA + 0x1b58)
        *e++ = 0;
}