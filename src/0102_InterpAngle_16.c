/* _InterpAngle@16 (96 B) - stdcall 4 args: wrap d=a2-a1 into
   [-0x7ff8,0x7ff8], then return a1 + d*a3/a4 (f7 6c /5 + f7 7c /7 chain on
   spilled a3/a4; FPO locals=4: a4, a3, d, result spills). */
long __stdcall w43c_iag(long a1, long a2, long a3, long a4)
{
    long d = a2 - a1;
    if (d > 0x7ff8)
        d -= 0xfff0;
    else if (d < -0x7ff8)
        d += 0xfff0;
    return a1 + d * a3 / a4;
}
