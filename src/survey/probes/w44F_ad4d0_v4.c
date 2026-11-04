/* rva 0xad4d0 (112 B) - queue step: retire entry at cursor w (no externs) */
void w44F_ad4d0(char *p)
{
    char *d;
    long *s;
    long w;
    long x;
    long b;
    long e;

    d = p + 0x549e;
    s = (long *)(d + 0x152e);
    --(*(long *)(d + 0x0c));
    w = *(long *)(d + 4);
    x = w + w;
    b = *(long *)(s + 3);
    b -= *(long *)(d + 0x1a + 9 * x);
    *(long *)(s + 3) = b;
    w = *(long *)(d + 4);
    e = *(long *)(s + 1);
    x = w + w;
    b = *(long *)(d + 0x1a + 9 * x) + e;
    *(long *)(s + 1) = b;
    if (b >= *(long *)(s + 2))
        *(long *)(s + 1) = b - *(long *)(s + 2);
    w = *(long *)(d + 4);
    w++;
    *(long *)(d + 4) = w;
    if (*(long *)(d + 8) <= w)
        *(long *)(d + 4) = 0;
}
