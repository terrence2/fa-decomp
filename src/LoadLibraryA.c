// _LoadLibraryA@4 @ rva 0xd342c (6 B) — KERNEL32 import pass-through thunk.
extern void *impLoadLibraryA[];
unsigned long __declspec(naked) __stdcall LoadLibraryA(void *a)
{
    __asm { jmp dword ptr [impLoadLibraryA] }
}
