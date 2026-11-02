/* _BoundsAnd@8 @ rva 0x11c20 — v2: deref arg2 (b) into the kept locals,
   compare arg1 (a); FA loads edx=[esp+8] (arg2) first pre-push, then
   ecx=[esp+8] post-push. */
typedef struct { short pad0, pad2, pad4, pad6; } w29c_A;

char __stdcall BoundsAnd_q(w29c_A *a, w29c_A *b)
{
    short s4, s6, s2, s0;

    s4 = b->pad4;
    if (s4 <= a->pad4)
        s4 = a->pad4;             /* max */
    s6 = b->pad6;
    if (s6 >= a->pad6)
        s6 = a->pad6;             /* min */
    s2 = b->pad2;
    if (s2 >= a->pad2)
        s2 = a->pad2;             /* min */
    s0 = b->pad0;
    if (s0 <= a->pad0)
        s0 = a->pad0;             /* max */
    if (s2 < s0)
        return 0;
    if (s4 > s6)
        return 0;
    return 1;
}