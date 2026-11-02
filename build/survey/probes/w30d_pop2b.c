// 0xd70a0 (21 B) — b: load first, advance after
__int64 __cdecl w30d_pop2b(void **pp)
{
    __int64 v;

    v = *(__int64 *)(*pp);
    *pp = (void *)((long)*pp + 8);
    return v;
}