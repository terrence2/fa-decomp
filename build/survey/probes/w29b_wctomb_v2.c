extern void __cdecl lockq(int n);
extern void __cdecl unlockq(int n);
extern int __cdecl wctombLkq(char *s, unsigned short wc);
extern unsigned int gctr1;
extern unsigned int gctr2;

int wctomb_q(char *s, unsigned short wc)
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
    r = wctombLkq(s, wc);
    if (flag) {
        unlockq(19);
    } else {
        gctr2 = gctr2 - 1;
    }
    return r;
}

int wctombB_q(char *s, unsigned short wc)
{
    int r;
    int flag;
    if (gctr1 == 0) {
        flag = 0;
        gctr2 = gctr2 + 1;
    } else {
        lockq(19);
        flag = 1;
    }
    r = wctombLkq(s, wc);
    if (flag == 0)
        gctr2 = gctr2 - 1;
    else
        unlockq(19);
    return r;
}