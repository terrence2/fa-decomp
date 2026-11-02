// __ZeroTail @ rva 0xdf880 — v7: guard-as-if(i<3) containing an unrotated
//   do-while (FA keeps the bottom test separate from the entry test).
int w27c_ZeroTailq7(unsigned long *arr, long n)
{
    int w, r, i;
    unsigned long *p;

    w = (int)(n / 32);
    r = (int)(n % 32);
    if (arr[w] & ~(-1U << (31 - r)))
        return 0;
    i = w + 1;
    if (i < 3) {
        p = arr + i;
        do {
            if (*p != 0)
                return 0;
            p += 1;
            i += 1;
        } while (i < 3);
    }
    return 1;
}
