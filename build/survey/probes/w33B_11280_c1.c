/* w33B_11280_c1.c -- _ResetKeyboard: zero the keyboard state block */
extern void __stdcall InitializeCriticalSection(void *pcs);
extern char w33b_cs[24];
extern unsigned short kbCount;
extern unsigned short kbHeadPtr;
extern unsigned long keyarray[64];
extern unsigned char qualStatus;
extern unsigned char keyFlags;
extern unsigned char keyboardInitialized;
extern unsigned short w33b_kbtp;

void _ResetKeyboard(void)
{
    unsigned long i;

    kbCount = 0;
    w33b_kbtp = 0;
    kbHeadPtr = 0;
    for (i = 0; i < 64; i++)
        keyarray[i] = 0;
    InitializeCriticalSection(&w33b_cs);
    qualStatus = 0;
    keyFlags = 0;
    keyboardInitialized = 1;
}