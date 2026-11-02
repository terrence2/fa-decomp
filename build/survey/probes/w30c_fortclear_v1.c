/* 0x205f0 — v1: clear fortPlayers with 0xffffffff (rep stosd fill) */
extern long _fortPlayers[8];

void __cdecl w30c_fortclear(void)
{
    long *p;
    int i;
    p = _fortPlayers;
    for (i = 0; i < 8; i++)
        *p++ = -1L;
}