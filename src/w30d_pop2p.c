// 0xd70a0 (21 B) — p: local pointer arithmetic keeps p in ecx
__int64 __cdecl w30d_pop2p(void **pp)
{
    long p;
    __int64 v;

    p = (long)*pp + 8;
    *pp = (void *)p;
    v = *(__int64 *)(p - 8);
    return v;
}