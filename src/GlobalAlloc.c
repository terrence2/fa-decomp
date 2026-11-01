// _GlobalAlloc@8 @ rva 0xd339c (6 B) — KERNEL32 import pass-through thunk.
extern void *impGlobalAlloc[];
unsigned long __declspec(naked) __stdcall GlobalAlloc(void *a, void *b)
{
    __asm { jmp dword ptr [impGlobalAlloc] }
}
