/* rva 0x4a740 (304960), 48 B - copy q->[0x10] into p->[0x6a] where
   q = *(char**)(p+0x196); call $FA$_t_44a770(p, q->[0x14]); q->[0x1c]=1. */
typedef void (cdecl *c2fun)(void *, unsigned long);

extern void __cdecl w34b_c2(void *p, unsigned long v);

void __cdecl w34b_4a740(void *p)
{
    char *q;
    q = *(char **)((char *)p + 0x196);
    *(unsigned long *)((char *)p + 0x6a) =
        *(unsigned long *)((char *)q + 0x10);
    w34b_c2(p, *(unsigned long *)((char *)q + 0x14));
    *((unsigned char *)q + 0x1c) = 1;
}