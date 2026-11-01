// _VirtualFree@12 @ rva 0xd33ae (6 B) — KERNEL32 import pass-through thunk.
extern void *impVirtualFree[];
unsigned long __declspec(naked) __stdcall VirtualFree(void *a, void *b, void *c)
{
    __asm { jmp dword ptr [impVirtualFree] }
}
