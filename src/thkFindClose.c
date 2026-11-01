// _FindClose@4 @ rva 0xd33f0 (6 B) — KERNEL32 import pass-through thunk.
extern void *impFindCloseThunk[];
unsigned long __declspec(naked) __stdcall FindClose(void *a)
{
    __asm { jmp dword ptr [impFindCloseThunk] }
}
