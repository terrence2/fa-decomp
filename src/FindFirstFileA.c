// _FindFirstFileA@8 @ rva 0xd33f6 (6 B) — KERNEL32 import pass-through thunk.
extern void *impFindFirstFileA[];
unsigned long __declspec(naked) __stdcall FindFirstFileA(void *a, void *b)
{
    __asm { jmp dword ptr [impFindFirstFileA] }
}
