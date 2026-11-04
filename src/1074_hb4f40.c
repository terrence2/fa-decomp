// $FA$_t_4b4f40 v2 — b evaluated first (pb -> ecx via [esp+8]), reused
// b/a locals: FA keeps b0/b1 in DX (pb's deref), pa ptr in ESI (the
// saved reg), a0 = AX 66 8b 06, a1 = CX 66 8b 4e 02; no push edi (b1
// loads late, after the early outs).
long __cdecl w43b_cmp2b(void *pa, void *pb)
{
    short b;
    short a;
    b = *(short *)pb;
    a = *(short *)pa;
    if (b > a)
        return -1;
    if (b < a)
        return 1;
    b = *(short *)((char *)pb + 2);
    a = *(short *)((char *)pa + 2);
    if (b > a)
        return -1;
    return (long)(b < a);
}