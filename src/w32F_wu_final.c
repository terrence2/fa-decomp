extern volatile long g_ticks;

void __fastcall w32f_wu(unsigned long t)
{
    volatile long l = (long)t;
    while (g_ticks < l)
        ;
}