// _VirtualAlloc@16 @ rva 0xd33a2 (6 B) — KERNEL32 import pass-through thunk.
extern void *impVirtualAlloc[];
unsigned long __declspec(naked) __stdcall VirtualAlloc(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impVirtualAlloc] }
}
