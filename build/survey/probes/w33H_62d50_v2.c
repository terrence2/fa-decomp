extern unsigned short currentT;         /* identity _currentT */

unsigned short __fastcall w33h_62d50(unsigned short c)
{
    unsigned s, t;
    s = currentT;  s &= 0x0ffffu;
    t = c;         t &= 0x0ffffu;
    if ((int)(s + t) < 0x7fff)
        return (unsigned short)(currentT + c);
    return (unsigned short)0x7fff;
}
