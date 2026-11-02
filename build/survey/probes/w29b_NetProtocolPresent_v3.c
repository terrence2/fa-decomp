// v3: goto-dispatch spelling — arms written after Ljoin so CL places them at
// the end with backward jmps (FA's shape).
extern unsigned __cdecl stubnp_a(unsigned short w);

void NetProtocolPresent_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    if (proto == 1)
        goto L2;
    if (4 <= proto && proto <= 5)
        goto L1;
    w = junk[1];
    goto Ljoin;
L1:
    w = 1;
    goto Ljoin;
L2:
    w = 2;
Ljoin:
    (void)(stubnp_a(w) != 0);
}