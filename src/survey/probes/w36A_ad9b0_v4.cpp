// w36A_ad9b0_v4: v2 matched all but the hi mask (CL folds
// (x>>16)&0xffff to bare shr; FA keeps and ebx,0xffff). Steer: stage
// the hi shift into a separate unsigned long temp the mask is applied
// to — in case CL 4.2 does not forward-sub across the temp.

struct socket_state {
    char pad[0x1c];
    unsigned char (__cdecl *event_fn)(unsigned long, unsigned long, unsigned long, struct socket_state *);
};

struct socket_state *socket_get_state_ptr(unsigned);

extern "C" void __cdecl netEvFail(unsigned long a, unsigned long lo, unsigned long hi, struct socket_state *st);

void NETProcessEvent(void *, unsigned, unsigned id, long e)
{
    unsigned long lo, hi, t;
    struct socket_state *st;

    t = (unsigned long)e;
    lo = t & 0xffff;
    t = t >> 16;
    hi = t & 0xffff;

    st = socket_get_state_ptr(id);
    if (st != 0) {
        if ((*st->event_fn)(id, lo, hi, st) == 0)
            netEvFail(id, lo, hi, st);
    }
}