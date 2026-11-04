/* C route: same logic, stores spelled before the call - CL scheduler will
 * interleave (or not) differently; judged against FA's push-interleaved form. */
extern long numComputers, thisComputer;
extern char curThing[];
extern void __stdcall w35h_p46(unsigned long, void *, unsigned long,
                               unsigned long);

void __stdcall MPRemoveCurObj(void)
{
    char buf[4];
    unsigned short id;

    if (numComputers == 1)
        return;
    if ((curThing[0x10] & 0x7f) != thisComputer)
        return;
    id = *(unsigned short *)(curThing + 0x74);
    *(unsigned short *)&buf[1] = id;
    buf[0] = 0x13;
    w35h_p46(0xffffffff, buf, 3, 1);
}