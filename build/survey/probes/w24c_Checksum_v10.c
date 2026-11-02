extern unsigned long __cdecl _lrotr(unsigned long, int);
struct CS { unsigned char *p; unsigned long sum; };
unsigned long __fastcall Checksum_q(const void *pv, unsigned long n)
{
    struct CS s;
    s.p = (unsigned char *)pv;
    s.sum = 0;
    while (n-- != 0) {
        s.sum = _lrotr(s.sum, 3) + *s.p++;
    }
    return s.sum;
}
