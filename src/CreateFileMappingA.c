// _CreateFileMappingA@24 @ rva 0xd3378 (6 B) — KERNEL32 import pass-through thunk.
extern void *impCreateFileMappingA[];
unsigned long __declspec(naked) __stdcall CreateFileMappingA(void *a, void *b, void *c, void *d, void *e, void *f)
{
    __asm { jmp dword ptr [impCreateFileMappingA] }
}
