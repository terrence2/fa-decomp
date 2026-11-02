// __ZeroTail @ rva 0xdf880 — v6: mask local seeded first, two-step mask
//   (shl then not as separate statements).
int w27c_ZeroTailq6(unsigned long *arr, long n)
{
    unsigned long m;
    int w, r, i;
    unsigned long *p;

    m = -1;
    w = (int)(n / 32);
    r = (int)(n % 32);
    m = ~(-1U << (31 - r));
    if (arr[w] & m)
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
