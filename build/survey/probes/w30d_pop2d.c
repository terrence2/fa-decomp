// 0xd70a0 (21 B) — d: advance via double deref of pp
__int64 __cdecl w30d_pop2d(void **pp)
{
    __int64 v;

    *(long *)pp += 8;
    v = ((__int64 *)*(long **)pp)[-1];
    return v;
}