// v2: same shape but arg spelled (short)(t*2), return int, t unsigned short.
extern short __fastcall Rand(int x);

unsigned short __fastcall w30g_randrange2(unsigned short x)
{
    short t;
    t = x * 0xb6;
    return Rand((short)(t * 2)) - t;
}