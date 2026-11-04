extern void __cdecl lockq(int n);
extern void __cdecl unlockq(int n);
extern unsigned long __cdecl wcstombsLkq(char *s, const unsigned short *ws,
                                          unsigned long n);
extern unsigned int gctr1;
extern unsigned int gctr2;

unsigned long wcstombs_q(char *s, const unsigned short *ws, unsigned long n)
{
    unsigned long r;
    int flag;
    if (gctr1 != 0) {
        lockq(19);
        flag = 1;
    } else {
        flag = 0;
        gctr2 = gctr2 + 1;
    }
    r = wcstombsLkq(s, ws, n);
    if (flag) {
        unlockq(19);
    } else {
        gctr2 = gctr2 - 1;
    }
    return r;
}