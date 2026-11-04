/* rva 0x11960 (dec 72032), 144 B _Clock@16 (stdcall, 4 args).
 * v4: corrected roles - FA's edi = A1 (base: lea+0x11, refs +0x1d / +0x15),
 * ebx = A3 (the WORD-div var), esi = A2 (Angles arg2 + the +4 d-src);
 * A4 (4th param) never held in a register: per-branch reloads [esp+0x1c].
 */
extern void __stdcall Angles(void *base, void *b, void *c, long d);

void __stdcall Clock(long p, void *q, void *w, void *z4)
{
    unsigned short u10;
    short tt;
    long t, d;

    Angles((char *)p + 0x11, q, w, 0);
    u10 = (unsigned short)((*(unsigned short *)w
                            - *(unsigned short *)((char *)p + 0x1d)
                            + 0xaaa) & 0xffff);
    t = (long)u10 * 12;
    t = t / 65520;
    tt = (short)t;
    *(unsigned short *)w = (unsigned short)tt;
    if (tt == 0)
        *(unsigned short *)w = 0xc;
    d = *(long *)((char *)q + 0x4) - *(long *)((char *)p + 0x15);
    if (d >= 0x7d000)
        *(unsigned short *)z4 = 1;
    else if (d <= -0x7d000)
        *(unsigned short *)z4 = 0xffff;
    else
        *(unsigned short *)z4 = 0;
}