// _WriteFile@20 @ rva 0xd3444 (6 B) — KERNEL32 import pass-through thunk.
extern void *impWriteFile[];
unsigned long __declspec(naked) __stdcall WriteFile(void *a, void *b, void *c, void *d, void *e)
{
    __asm { jmp dword ptr [impWriteFile] }
}
