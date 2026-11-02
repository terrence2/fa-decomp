// __ZeroTail @ rva 0xdf880 (100 B) — v2: arg2 is the used one; mask seeded
//   early (b=-1), index declared first.
int __cdecl w27c_ZeroTail(int unused, long n)
{
    long w, r, i;
    unsigned long b;
    unsigned long *arr;
    b = -1;
    w = n / 32;
    r = n % 32;
    arr = (unsigned long *)(long)n;
    if (arr[w] & ((b << (31 - r)) ^ 0xffffffffU))
        return 0;
    for (i = w + 1; i < 3; i++)
        if (arr[i] != 0)
            return 0;
    return 1;
}
