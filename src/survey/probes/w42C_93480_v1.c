/* w42C cand5: unnamed @0x93480 (80 B) — cdecl 1 param, void return. */
typedef void (__cdecl *w42c_fn)(void *);

void __cdecl w42c_93480(void *p)
{
    long *t;
    long *m;

    t = *(long **)((char *)p + 0x17e);
    *t = 0x4931c0;
    *((char *)t + 0x10) = 0;
    *((char *)t + 0x11) = 0;
    *((char *)t + 0x12) = 1;
    ((w42c_fn *)(*(long **)p))[4](p);
    m = *(long **)((char *)p + 0x182);
    (*(w42c_fn *)m)(p);
    *(long *)((char *)p + 0x82) = 0;
}
