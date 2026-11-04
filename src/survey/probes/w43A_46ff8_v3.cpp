// FA: ebp frame; m homed [ebp-4]; long jcc; fresh ebp arg reloads; 3 dead jmps
struct F24_POINT { long f0; long f4; };
extern "C" long __stdcall w43bMD(long, long, long);

long IntersectB(F24_POINT *p, long a, long b)
{
    volatile long m;
    if (p->f4 > a) return b;
    m = w43bMD(p->f0 >> 8, a >> 8, p->f4 >> 8);
    if (m <= b) return m;
    return b;
}
