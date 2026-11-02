// ?socket_get_state_ptr@@YAPAUsocket_state@@I@Z @ 0xa30c0 (64 B) — v1
// cdecl C++: socket_state* (unsigned int). count compare as
// cmp [socket_list],edx entry+jlatch; id load in body; f0c==id via ebp load.
struct socket_state {
    unsigned char s0[0xc];
    long s0c;
    unsigned char s10[8];
    unsigned char s18;
    unsigned char pad[0x32 - 0x19];
};

struct SOCKET_STATE_LIST {
    long count;
    unsigned char pad[0x420];
    struct socket_state ss[2];
};

extern struct SOCKET_STATE_LIST socket_list;

struct socket_state *socket_get_state_ptr(unsigned int id)
{
    struct socket_state *e = &socket_list.ss[0];
    long i;
    for (i = 0; i < socket_list.count; i++) {
        if (e->s18) {
            if (e->s0c == id)
                return e;
        }
        e = (struct socket_state *)((char *)e + 0x32);
    }
    return 0;
}