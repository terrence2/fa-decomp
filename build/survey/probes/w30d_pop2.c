// 0xd70a0 (21 B) — v1: pop two dwords as __int64, advance pointer
__int64 __cdecl w30d_pop2(void **pp)
{
    __int64 v;

    *pp = (void *)((long)*(long **)pp + 8);
    v = *(__int64 *)((long)*(long **)pp - 8);
    return v;
}