// _lstrcpyA@8 @ rva 0xd3456 (6 B) — KERNEL32 import pass-through thunk.
extern void *implstrcpyA[];
unsigned long __declspec(naked) __stdcall lstrcpyA(void *a, void *b)
{
    __asm { jmp dword ptr [implstrcpyA] }
}
