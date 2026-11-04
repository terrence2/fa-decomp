// w40G_1680_v4 — decl order n (count) BEFORE t (temp): FA saved-reg plan
// esi=count, edi=temp (v3 gave the inversion).
void w40g_copy(void *dst, void *src, unsigned long len)
{
    char b;
    long n, t, m;
    n = len >> 2;
    while (n != 0) {
        t = *(long *)src;
        src = (long *)((char *)src + 4);
        *(long *)dst = t;
        dst = (long *)((char *)dst + 4);
        n--;
    }
    m = len & 3;
    while (m != 0) {
        b = *(char *)src;
        src = (long *)((char *)src + 1);
        *(char *)dst = b;
        dst = (long *)((char *)dst + 1);
        m--;
    }
}