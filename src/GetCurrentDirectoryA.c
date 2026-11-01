// _GetCurrentDirectoryA@8 @ rva 0xd345c (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetCurrentDirectoryA[];
unsigned long __declspec(naked) __stdcall GetCurrentDirectoryA(void *a, void *b)
{
    __asm { jmp dword ptr [impGetCurrentDirectoryA] }
}
