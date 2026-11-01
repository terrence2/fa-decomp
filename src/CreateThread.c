// _CreateThread@24 @ rva 0xd33cc (6 B) — KERNEL32 import pass-through thunk.
extern void *impCreateThread[];
unsigned long __declspec(naked) __stdcall CreateThread(void *a, void *b, void *c, void *d, void *e, void *f)
{
    __asm { jmp dword ptr [impCreateThread] }
}
