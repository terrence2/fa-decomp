// __ZeroTail @ rva 0xdf880 (915584, 100 B) — CRT-band bit helper: only arg1
//   used (as both bit index and 3-dword array base): w = arg1/32 (edi),
//   cl = 31 - arg1%32, mask = ~(-1 << cl) = low (32-r) bits; fail if
//   arr[w] & mask, else scan words w+1..2 for zero, ret 1 iff all clear.
int __cdecl w27c_ZeroTail(long n)
{
    long w;
    long r;
    unsigned long mask;
    unsigned long *arr;
    long i;
    w = n / 32;
    r = n % 32;
    mask = ~(unsigned long)0xffffffff << (31 - r);
    arr = (unsigned long *)(long)n;
    if ((unsigned long)arr[w] & mask)
        return 0;
    for (i = w + 1; i < 3; i++)
        if (arr[i] != 0)
            return 0;
    return 1;
}
