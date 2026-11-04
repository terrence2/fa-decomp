/* w33B_11280_c2.c -- v2: stores before the call, dllimport imp call */
extern unsigned short kbCount;
extern unsigned short kbHeadPtr;
extern unsigned long keyarray[64];
extern unsigned char qualStatus;
extern unsigned char keyFlags;
extern unsigned char keyboardInitialized;
extern unsigned short w33b_kbtp;
extern char w33b_cs[24];
__declspec(dllimport) void __stdcall InitializeCriticalSection(void *pcs);

void _ResetKeyboard(void)
{
    unsigned long i;

    kbCount = 0;
    w33b_kbtp = 0;
    kbHeadPtr = 0;
    for (i = 0; i < 64; i++)
        keyarray[i] = 0;
    qualStatus = 0;
    keyFlags = 0;
    InitializeCriticalSection(&w33b_cs);
    keyboardInitialized = 1;
}