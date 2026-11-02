extern unsigned long __cdecl _lrotr(unsigned long, int);

unsigned long __fastcall Checksum_q(const void *pv, unsigned long n)
{
    unsigned long volatile sum = 0;
    const unsigned char volatile *p = (const unsigned char volatile *)pv;
    while (n-- != 0) {
        sum = _lrotr(sum, 3) + *p++;
    }
    return sum;
}
