extern void __cdecl lockq(int n);
extern void __cdecl unlockq(int n);
extern int __cdecl mbtowcLkq(void *pwc, const char *s, unsigned long n);
extern unsigned int gctr1;
extern unsigned int gctr2;

int mbtowc_q(void *pwc, const char *s, unsigned long n)
{
    int r;
    int flag;
    if (gctr1 != 0) {
        lockq(19);
        flag = 1;
    } else {
        flag = 0;
        gctr2 = gctr2 + 1;
    }
    r = mbtowcLkq(pwc, s, n);
    if (flag) {
        unlockq(19);
    } else {
        gctr2 = gctr2 - 1;
    }
    return r;
}