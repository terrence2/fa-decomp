// _FindNextFileA@8 @ rva 0xd3402 (6 B) — KERNEL32 import pass-through thunk.
extern void *impFindNextFileA[];
unsigned long __declspec(naked) __stdcall FindNextFileA(void *a, void *b)
{
    __asm { jmp dword ptr [impFindNextFileA] }
}
