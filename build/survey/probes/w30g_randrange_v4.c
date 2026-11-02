// v4: unsigned short param + return; 16-bit ops on cx/si per wave-5 d71.
extern short __fastcall Rand(int x);

unsigned short __fastcall w30g_randrange4(unsigned short x)
{
    x = x * 0xb6;
    return Rand(x * 2) - x;
}