// _ReadFile@20 @ rva 0xd343e (6 B) — KERNEL32 import pass-through thunk.
extern void *impReadFile[];
unsigned long __declspec(naked) __stdcall ReadFile(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impReadFile] }
}
