/* rva 0x8ff00 (112 B, __cdecl, 1 ptr arg): vtable state dispatch.
 * p's object slot +0x16e holds a handle h. Three independent tests drive
 * the two vtable dispatch arms:
 *   - when *(long*)(p+0xe) != 0xcf: write command ids through the vtable
 *     table pointer *p - [v+0x14] = 0x12, [v+0x18] = *(long*)(p+0xe),
 *     then call vtable[0] with p. All three loads of *p, the push of p
 *     between them and the doubled reloads are FA's scheduler shape, kept
 *     verbatim by the transplant.
 *   - if byte p[0x42] and byte p[0x4f] and *(long*)(p+0x6a) are all
 *     truthy: va = *(void**)(h+0x14); *(long*)(p+0x196) = va; call
 *     *(fn**)((char*)va+0xc) with p; clear byte h[8].
 *   - else (or when +0xe == 0xcf skips the first arm): [v+0x14] = 0x2d
 *     and vtable[0](p) again - the fall-through arm lives at the end, one
 *     shared exit.
 * No absolute fixups: every operand is a struct offset or an indirect
 * vtable call.
 */
void __cdecl w44e_dispatch(char *p)
{
    void *v, *h, *va;
    if (*(long *)(p + 0xe) != 0xcf) {
        v = *(void **)p;
        *(long *)((char *)v + 0x14) = 0x12;
        v = *(void **)p;
        *(long *)((char *)v + 0x18) = *(long *)(p + 0xe);
        v = *(void **)p;
        (*(void (__cdecl **)(void *))v)(p);
    }
    if (p[0x42] && p[0x4f] && *(long *)(p + 0x6a)) {
        h = *(void **)(p + 0x16e);
        va = *(void **)((char *)h + 0x14);
        *(long *)(p + 0x196) = (long)va;
        (*(void (__cdecl **)(void *))((char *)va + 0xc))(p);
        *(char *)((char *)h + 8) = 0;
    } else {
        v = *(void **)p;
        *(long *)((char *)v + 0x14) = 0x2d;
        v = *(void **)p;
        (*(void (__cdecl **)(void *))v)(p);
    }
}