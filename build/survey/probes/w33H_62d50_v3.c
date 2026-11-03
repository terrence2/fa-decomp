/* v3 = v2 polarity flip: if ((int)(s+t) >= 0x7fff) return 0x7fff; else
 * fall into the add path.  CL scheme: fall = then-return inline,
 * jcc(not C) = jl -> the else-return (add) — FA's exact arrangement. */
extern unsigned short currentT;         /* identity _currentT */

unsigned short __fastcall w33h_62d50(unsigned short c)
{
    unsigned s, t;
    s = currentT;  s &= 0x0ffffu;
    t = c;         t &= 0x0ffffu;
    if ((int)(s + t) >= 0x7fff)
        return (unsigned short)0x7fff;
    return (unsigned short)(currentT + c);
}
