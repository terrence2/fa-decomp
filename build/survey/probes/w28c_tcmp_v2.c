// 0xa7640 — v2 prebool second compare
long __cdecl w28c_tcmp(char *a, char *b)
{
    long k1, k2, r;

    k1 = (*(long *)(a + 2) << 16) + *(long *)a;
    k2 = (*(long *)(b + 2) << 16) + *(long *)b;
    if (k1 < k2) return -1;
    r = 0;
    r = k1 > k2;
    return r;
}
