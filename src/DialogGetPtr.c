// @DialogGetPtr@4 @ rva 0x87400 — d = curDialog->f4; for n > 1 walk f2
//   n-1 times inside a do/while (probe d57 exact: 16-bit cmp, and 0xffff,
//   dec/mov/dec/jne loop shape came out naturally).
extern void *curDialog;

int __fastcall DialogGetPtr_q(int a)
{
    long d = (long)curDialog;
    unsigned short n = (unsigned short)a;
    d = *(long *)((char *)d + 4);
    if (n > 1) {
        unsigned long i = n;
        --i;
        do { d = *(long *)((char *)d + 2); } while (--i);
    }
    return d;
}
