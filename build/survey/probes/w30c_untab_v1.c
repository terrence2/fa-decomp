/* 0x66a20 — v1: copy chars from *src into *dst while c > 1, skip terminator
   fastcall: dst in ecx, src in edx */
void __fastcall w30c_untab(unsigned char **dst, unsigned char **src)
{
    unsigned char *s, *d;
    unsigned char b;
    s = *src;
    d = *dst;
    while (*s > 1) {
        b = *s;
        s++;
        *d = b;
        d++;
    }
    s++;
    *src = s;
    *dst = d;
}