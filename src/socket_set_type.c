// ?socket_set_type@@YADPAUsocket_state@@W4SOCK_TYPE@@@Z @ rva 0xa3160
// (16 B, FPO fpo/esp params=2 dwords) — stores the type enum at +0x14 and
// returns char 1 (b0 01); 8b ff tail pad is census filler.
char socket_set_type(struct socket_state *p, unsigned t)
{
    ((unsigned *)p)[5] = t;
    return 1;
}