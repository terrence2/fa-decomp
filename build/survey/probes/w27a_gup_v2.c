// @G_UPoint@8 v2 — two externs force the double _cb load (a1 + 8b 35) and
// keep the value in eax (imul edx, add [esi+0xa]); lineStats store via
// extern-array index (base imm32 in disp32).
extern unsigned char w27a_cFT;   /* _cFillType */
extern unsigned char w27a_cCol;  /* _cColor */
extern char *w27a_cb;            /* _cb */
extern char *w27a_cb2;           /* _cb (2nd load) */
extern char w27a_lS[];           /* _lineStats */
extern void __stdcall G_UHline_f(int a, int b, int c);   /* _G_UHline@12 */
void __fastcall w27a_gup_q(long x, long y)
{
    unsigned long a;
    if (w27a_cFT == 0)
    {
        a = *(long *)(w27a_cb + 2);
        a = a * y + *(long *)(w27a_cb2 + 0xa);
        *(unsigned char *)(a + x) = w27a_cCol;
        w27a_lS[y] = (char)0xff;
        return;
    }
    G_UHline_f(x, x, y);
    return;
}
