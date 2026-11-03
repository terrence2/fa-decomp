extern void *__stdcall WRGetLayer(int, int);

void __cdecl WRWeatherEffects(int p1, int p2, int p3, int *p4)
{
    int a, d, m, t, v;
    unsigned b;
    void *l1, *l2;
    a = p2;
    d = p3;
    if (d < a) { t = a; a = d; d = t; }
    l1 = WRGetLayer(a, 0);
    l2 = WRGetLayer(d, 0);
    m = 100;
    while ((unsigned long)l1 <= (unsigned long)l2) {
        v = *(unsigned char *)((char *)l1 + 0x14e + (unsigned char)p1);
        if (v < m)
            m = v;
        l1 = (char *)l1 + 0x160;
    }
    if (p4 != 0)
        *p4 = *(int *)((char *)l2 + 0x22) << 0x10;
}