/* 0xb0ed0 @WRCanSee@8 0x80 — v2: q2 = WRWE return (stored like FA 89442424),
 * Dist first then min (FA's post-call min, mn in ecx), no rc2 long temp,
 * out taken by WRWE (spilled, reloaded after call), d0 live in a reg.
 */
extern long __cdecl WRWeatherEffects(long a, long b, long c, void *out);
extern long __stdcall Dist(long a, long b);

char __fastcall WRCanSee(void *p1, void *p2)
{
    void *d1, *d2;
    long d0, dres, mn, out;
    volatile long q1, q2, q3, den;
    d1 = p1;
    d2 = p2;
    q2 = WRWeatherEffects(0L, *(long *)((char *)d1 + 0x15),
                          *(long *)((char *)d2 + 0x15), &out);
    d0 = *(long *)((char *)d2 + 5);
    den = 0x64;
    q1 = (long)*(unsigned short *)((char *)d0 + 0x3b) << 16;
    q3 = (q1 * q2) / den;
    dres = Dist((long)d1 + 0x11, (long)d2 + 0x11);
    mn = out;
    if (mn >= q3)
        mn = q3;
    return (char)(mn >= dres);
}