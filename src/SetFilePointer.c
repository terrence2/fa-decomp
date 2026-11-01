// _SetFilePointer@16 @ rva 0xd3438 (6 B) — KERNEL32 import pass-through thunk.
extern void *impSetFilePointer[];
unsigned long __declspec(naked) __stdcall SetFilePointer(void *a, void *b, void *c, void *d)
{
    __asm { jmp dword ptr [impSetFilePointer] }
}
