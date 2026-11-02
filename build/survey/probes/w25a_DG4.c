/* variant 4: page temp then d = page + m (sum materialized into d's home) */
extern unsigned char *__fastcall DialogGetPtr_q(unsigned long p);  /* @DialogGetPtr@4 */
extern char *__fastcall PageText_q(long w, unsigned long d);       /* ?PageText@@YIPADJ@Z */

unsigned char *__fastcall DialogGetString_q(unsigned long p)
{
    unsigned char *q;
    unsigned long tw;
    short w;
    unsigned char *d;
    unsigned char *page;
    unsigned short n;
    unsigned char *r;

    q = DialogGetPtr_q(p);
    tw = *(unsigned short *)q & 0x7fff;
    switch (tw) {
    case 0:
        return (unsigned char *)(*(unsigned long *)(q + 0x1a));
    case 2:
        return (unsigned char *)(*(unsigned long *)(q + 0x14));
    case 4:
        w = *(short *)(q + 0x1a);
        d = *(unsigned char **)(q + 0x20);
        n = *(unsigned short *)(q + 0x24);
        if (n & 0x8000) {
            page = PageText_q(w, d);
            d = page + (n & 0x7fff);
            return d;
        }
        if (w != 0) {
            do {
                do {
                    r = d;
                } while (*d++);
                w--;
            } while (w != 0);
        }
        return d;
    }
    return 0;
}
