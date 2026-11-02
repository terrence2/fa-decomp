/* _BoundsAnd@8 @ rva 0x11c20 (112 B; 96 code + 13 pad). char __stdcall,
 2 ptr args. edx=arg2 loaded first, ecx=arg1 (reloaded after push ebx).
 Short max/min math on fields 0,2,4,6 of both structs, then overlap test. */
typedef struct { short pad0, pad2, pad4, pad6; } w29c_A;

char __stdcall BoundsAnd_q(w29c_A *p2, w29c_A *p1)
{
    short s4, s6, s2, s0;

    s4 = p2->pad4;
    if (s4 <= p1->pad4)
        s4 = p1->pad4;            /* max(s4) */
    s6 = p2->pad6;
    if (s6 >= p1->pad6)
        s6 = p1->pad6;            /* min(s6) */
    s2 = p2->pad2;
    if (s2 >= p1->pad2)
        s2 = p1->pad2;            /* min(s2) */
    s0 = p2->pad0;
    if (s0 <= p1->pad0)
        s0 = p1->pad0;            /* max(s0) */
    if (s2 < s0)
        return 0;
    if (s4 > s6)
        return 0;
    return 1;
}