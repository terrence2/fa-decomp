/* FreeTextStuff v2: stdcall void(void); free fmtText[n*17] slot + handle,
 * music-off, textNum--. FA: a1/mov ecx,eax/shl4/add fold; [eax*4] loads. */
extern char dirTVYTime8;    /* ?dirTVYTime@@3JA+0x8 (byte) */
extern void *__fastcall MMFreePtr(void *);
extern void *__fastcall MMFreeHandle(void *);
extern void __fastcall w38e_musoff(void);
extern long ftextNum;      /* -> _textNum */
extern unsigned long fmtText[];

void __stdcall FreeTextStuff(void)
{
    unsigned long *pp;
    unsigned long n;
    n = (unsigned long)ftextNum;
    pp = fmtText + n * 17;
    if (*pp) {
        MMFreePtr((void *)*pp);
        *pp = 0;
    }
    if (pp[9]) {
        MMFreeHandle((void *)pp[9]);
        pp[9] = 0;
    }
    if (dirTVYTime8)
        w38e_musoff();
    ftextNum = ftextNum - 1;
}
