// _CreateFileA@28 @ rva 0xd3384 (6 B) — KERNEL32 import pass-through thunk.
extern void *impCreateFileA[];
unsigned long __declspec(naked) __stdcall CreateFileA(void *a, void *b, void *c, void *d, void *e, void *f, void *g)
{
    __asm { jmp dword ptr [impCreateFileA] }
}
