// @G_UPoint@8 @ rva 0x95830 — fastcall (ecx=x, edx=y); if (_cFillType==0)
//   bl=_cColor; a = *(_cb+2) * edx + *(_cb+0xa); *(char*)(a+x) = _cColor;
//   else G_UHline(x, x, y) (push edx, push ecx, push ecx).
extern unsigned char w27a_cFT;   /* _cFillType */
extern unsigned char w27a_cCol;  /* _cColor */
extern char *w27a_cb;            /* _cb */
extern void __stdcall G_UHline_f(int a, int b, int c);   /* _G_UHline@12 */
void __fastcall w27a_gup_q(long x, long y)
{
    char *cb = w27a_cb;
    unsigned long a;
    if (w27a_cFT == 0)
    {
        a = *(long *)(cb + 2);
        a = a * y + *(long *)(cb + 0xa);
        *(unsigned char *)(a + x) = w27a_cCol;
        return;
    }
    G_UHline_f(x, x, y);
    return;
}
