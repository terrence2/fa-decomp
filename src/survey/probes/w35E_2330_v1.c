// chunk @ rva 0x2330 (48 B: 34 B code + 14 B 8da424 census pad) -- timer
// deadline stamp: *p[2] = timerTicks+0x400; if (!p_byte@0x1a) p[1] = 4;
// fpo/esp, no callee-saves; a1 moffs load of _timerTicks.
extern long timerTicks;

void w35_2330(long *p)
{
    long t;
    t = timerTicks + 0x400;
    p[2] = t;
    if (((char *)p)[0x1a] == 0)
        p[1] = 4;
}