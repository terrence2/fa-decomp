// _localeconv @ rva 0xe1ec0 (6 B, FPO cbProlog=0)
// FA asm: a1 68 be 51 00  mov eax,ds:0x51be68 (= __no_lead_zeros+0x3c)
//         c3
//   -> returns the struct lconv* that lives in the CRT data region; the
//      chunk name has ONE underscore, so the C identifier is `localeconv`.
extern unsigned char _no_lead_zeros[];

char *__cdecl localeconv(void)
{
    return (char *)(unsigned long)*(const int *)(_no_lead_zeros + 0x3c);
}