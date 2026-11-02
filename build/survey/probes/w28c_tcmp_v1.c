// 0xa7640 ?T_CompareTlist@@YAJPAX0@Z (64 B) — v1
long __cdecl w28c_tcmp(char *a, char *b)
{
    long k1, k2;

    k1 = (*(long *)(a + 2) << 16) + *(long *)a;
    k2 = (*(long *)(b + 2) << 16) + *(long *)b;
    if (k1 < k2) return -1;
    return k1 > k2;
}
