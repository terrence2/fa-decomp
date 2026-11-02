/* _BoundsAnd@8 @ rva 0x11c20 — v3: nested ifs so the false epilogue lands
   at the end (FA: cmp bx,dx / jl / cmp si,di / jg / al=1 / ret / false). */
typedef struct { short pad0, pad2, pad4, pad6; } w29c_A;

char __stdcall BoundsAnd_q(w29c_A *a, w29c_A *b)
{
    short s4, s6, s2, s0;

    s4 = b->pad4;
    if (s4 <= a->pad4)
        s4 = a->pad4;
    s6 = b->pad6;
    if (s6 >= a->pad6)
        s6 = a->pad6;
    s2 = b->pad2;
    if (s2 >= a->pad2)
        s2 = a->pad2;
    s0 = b->pad0;
    if (s0 <= a->pad0)
        s0 = a->pad0;
    if (s2 >= s0)
        if (s4 <= s6)
            return 1;
    return 0;
}