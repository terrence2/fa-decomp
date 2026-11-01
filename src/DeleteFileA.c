// _DeleteFileA@4 @ rva 0xd344a (6 B) — KERNEL32 import pass-through thunk.
extern void *impDeleteFileA[];
unsigned long __declspec(naked) __stdcall DeleteFileA(void *a)
{
    __asm { jmp dword ptr [impDeleteFileA] }
}
