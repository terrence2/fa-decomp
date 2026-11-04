// v5: switch spelling.
extern unsigned __cdecl stubnp_a(unsigned short w);

void NetProtocolPresent_q(long proto)
{
    unsigned short junk[2];
    unsigned short w;
    switch (proto) {
    case 1:
        w = 2;
        break;
    case 4:
    case 5:
        w = 1;
        break;
    default:
        w = junk[1];
    }
    (void)(stubnp_a(w) != 0);
}