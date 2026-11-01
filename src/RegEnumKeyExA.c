// _RegEnumKeyExA@32 @ rva 0xd36a2 (14 B, gap chunk — 6-B IAT pass-through
// plus an 8-B int3 run, census filler) — ADVAPI32 RegEnumKeyExA import
// thunk. ff 25 jmp [imp-wave-15 form]: extern imp-array + one map
// _impRegEnumKeyExA=__imp__RegEnumKeyExA (stub def carries NO @N); decl
// stdcall with 8 void* params so CL decorates _RegEnumKeyExA@32 like the
// chunk symbol.
extern void *impRegEnumKeyExA[];
long __declspec(naked) __stdcall RegEnumKeyExA(void *a, void *b, void *c,
                                               void *d, void *e, void *f,
                                               void *g, void *h)
{
    __asm { jmp dword ptr [impRegEnumKeyExA] }
}