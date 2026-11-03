/* rva 0x62d50 (48 B): u16 saturation add: FA reads ax = word _currentT
 * (66 a1), pushes esi, edx=ecx;edx&=0xffff; esi=eax;esi&=0xffff;
 * edx+=esi; cmp edx,0x7fff; jl -> add ax,cx; ret; else mov ax,0x7fff. */
extern unsigned short currentT;         /* identity _currentT */

unsigned short __fastcall w33h_62d50(unsigned short c)
{
    unsigned s = currentT;  s &= 0x0ffffu;
    unsigned t = c;         t &= 0x0ffffu;
    if ((int)(s + t) < 0x7fff)
        return (unsigned short)(currentT + c);
    return (unsigned short)0x7fff;
}
