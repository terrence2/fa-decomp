// __ZeroTail @ rva 0xdf880 (915584, 100 B) — v5: CORRECTED signature —
//   FA reads arg2 = index n into esi at entry and arg1 = array LATE at the
//   test ([esp+0x10] straddle), mask seeded -1 / shl / not in ebx.
int w27c_ZeroTailq(unsigned long *arr, long n)
{
    int w, r, i;
    unsigned long *p;

    w = (int)(n / 32);
    r = (int)(n % 32);
    if (arr[w] & ~(-1U << (31 - r)))
        return 0;
    i = w + 1;
    if (i >= 3)
        return 1;
    p = arr + i;
    do {
        if (*p != 0)
            return 0;
        p += 1;
        i += 1;
    } while (i < 3);
    return 1;
}
