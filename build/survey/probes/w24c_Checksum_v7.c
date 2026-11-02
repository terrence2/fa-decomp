extern unsigned long __cdecl _lrotr(unsigned long, int);
unsigned long __fastcall Checksum_q(const void *pv, unsigned long n)
{
    unsigned char * volatile p;
    unsigned long sum;
    p = (unsigned char *)pv;
    sum = 0;
    while (n-- != 0) {
        sum = _lrotr(sum, 3) + *p++;
    }
    return sum;
}
