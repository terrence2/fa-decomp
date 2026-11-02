// v4: ternary spelling.
extern unsigned __cdecl stubnp_a(unsigned short w);

void NetProtocolPresent_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    w = (proto == 1) ? 2 : ((4 <= proto && proto <= 5) ? 1 : junk[1]);
    (void)(stubnp_a(w) != 0);
}