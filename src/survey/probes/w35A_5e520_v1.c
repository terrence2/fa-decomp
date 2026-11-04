extern char w35a_thing[];  /* -> _curThing (0x507838); +0xe8 = ptr field */

long w35a5e520(void)
{
    long p;
    char c;
    p = *(long *)(w35a_thing + 0xe8);
    if (p == 0) return 100;
    c = *(char *)p;
    if (c & 8) return 1;
    if (c & 0x10) return 2;
    return 100;
}
