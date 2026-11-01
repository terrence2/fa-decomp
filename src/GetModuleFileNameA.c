// _GetModuleFileNameA@12 @ rva 0xd3462 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetModuleFileNameA[];
unsigned long __declspec(naked) __stdcall GetModuleFileNameA(void *a, void *b, void *c)
{
    __asm { jmp dword ptr [impGetModuleFileNameA] }
}
