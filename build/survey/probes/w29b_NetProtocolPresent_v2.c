extern unsigned __cdecl stubnp_a(unsigned short w);

void NetProtocolPresent_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    stubnp_a(w);
}

void NetProtocolPresentB_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    if (proto == 1) { w = 2; goto Ljoin; }
    if (4 <= proto && proto <= 5) { w = 1; goto Ljoin; }
    w = junk[1];
Ljoin:
    (void)(stubnp_a(w) != 0);
}