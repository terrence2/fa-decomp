// __ZeroTail @ rva 0xdf880 — v3: (a) arg2 used; (b) w first (hoping edi);
//   (c) FA loop shape: guard i<3 then p = arr+i, do-while (++i<3).
int __cdecl w27c_ZeroTail3(int unused, long n)
{
    int w, r, i;
    unsigned long m;
    unsigned long *arr;
    unsigned long *p;
    w = n / 32;
    r = n % 32;
    arr = (unsigned long *)(long)n;
    m = (0xffffffffU << (31 - r)) ^ 0xffffffffU;
    if (arr[w] & m)
        return 0;
    i = w + 1;
    if (i < 3) {
        p = (unsigned long *)((char *)arr + (i << 2));
        do {
            if (*p != 0)
                return 0;
            p += 1;
            i++;
        } while (i < 3);
    }
    return 1;
}
