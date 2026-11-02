// __IncMan @ rva 0xdf8f0 — C v2 (do-while with body-top r test)
extern unsigned long __cdecl t4e2cf0(unsigned long v, unsigned long m, unsigned long *w);

void __cdecl IncManq(unsigned long *man, long bit)
{
    unsigned long mask, r;
    unsigned long *w;
    long i;

    i = bit / 32;
    mask = 1 << (31 - bit % 32);
    w = &man[i];
    r = t4e2cf0(*w, mask, w);
    if (--i < 0)
        return;
    w = &man[i];
    do
    {
        if (r == 0)
            return;
        r = t4e2cf0(*w, 1, w);
        w--;
    } while (--i >= 0);
}
