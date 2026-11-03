extern void *__stdcall WRGetLayer(int, int);

void __cdecl WRWeatherEffects(int p1, int p2, int p3, int *p4)
{
    int a;
    int d;
    void *l1;
    void *l2;
    unsigned m;
    unsigned b;
    unsigned v;
    a = p2;
    d = p3;
    if (d < a) {
        a = p3;
        d = p2;
    }
    l1 = WRGetLayer(a, 0);
    l2 = WRGetLayer(d, 0);
    if ((unsigned)l2 < (unsigned)l1)
        m = 100;
    else {
        m = 100;
        b = 0;
        b = (unsigned char)p1;
        v = 0;
        while ((unsigned)l1 <= (unsigned)l2) {
            v = *(unsigned char *)((char *)l1 + 0x14e + b);
            if (v < m)
                m = v;
            l1 = (char *)l1 + 0x160;
        }
    }
    if (p4 != 0)
        *p4 = *(int *)((char *)l2 + 0x22) << 0x10;
}