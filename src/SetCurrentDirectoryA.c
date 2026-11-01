// _SetCurrentDirectoryA@4 @ rva 0xd3330 (6 B) — KERNEL32 import pass-through
// thunk.
extern void *impSetCurrDirA[];
unsigned long __declspec(naked) __stdcall SetCurrentDirectoryA(const char *path)
{
    __asm { jmp dword ptr [impSetCurrDirA] }
}
