// w40G_92f00_v2 — two-step vtable deref spelled with ** cast so CL emits
// mov eax,[esi+field]; call [eax] (one-level folding defeats the FA shape);
// slot store via separate pointer local for FA's early pop esi.
extern void t492f50(void *o);
extern void t4930f0(void *o);

void w40g_vte(void *o)
{
    void *vt;
    void *slot;
    t492f50(o);
    t4930f0(o);
    vt = *(void **)((char *)o + 0x186);
    (*(void (__cdecl **)(void *))vt)(o);
    vt = *(void **)((char *)o + 0x176);
    (*(void (__cdecl **)(void *))vt)(o);
    vt = *(void **)((char *)o + 0x176);
    slot = *(void **)((char *)o + 0x17e);
    *(void **)slot = ((void **)vt)[1];
}