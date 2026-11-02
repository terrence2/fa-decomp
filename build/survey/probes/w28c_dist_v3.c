// 0xc2a7c _Dist@8 — v3: unsigned abs values (FA max-swaps use unsigned jae)
long __stdcall w28c_dist(long *a, long *b)
{
    unsigned long x, y, z, t;

    x = *(unsigned long *)a - *(unsigned long *)b;
    if ((long)x < 0) x = -x;
    y = *(unsigned long *)(a + 1) - *(unsigned long *)(b + 1);
    if ((long)y < 0) y = -y;
    z = *(unsigned long *)(a + 2) - *(unsigned long *)(b + 2);
    if ((long)z < 0) z = -z;
    if (y < z) { t = y; y = z; z = t; }
    if (x < y) { t = x; x = y; y = t; }
    return x + (y >> 2) + (z >> 2);
}
