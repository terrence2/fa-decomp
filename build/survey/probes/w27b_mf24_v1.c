// 0x11730 _MatchF24@12 (80 B) — v1
extern short serviceTicks;   /* identity: _serviceTicks */

void __stdcall MatchF24q(long *p, long tgt, long sc)
{
    long cur;
    long d;

    cur = *p;
    if (tgt == cur)
        return;
    if (sc == 0)
        return;
    d = (long)serviceTicks * sc;
    d = d >> 8;
    if (tgt > cur) {
        cur = cur + d;
        *p = cur;
        if (tgt < cur)
            *p = tgt;
    } else {
        cur = cur - d;
        *p = cur;
        if (tgt > cur)
            *p = tgt;
    }
}