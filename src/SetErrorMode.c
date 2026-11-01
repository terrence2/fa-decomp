// _SetErrorMode@4 @ rva 0xd3432 (6 B) — KERNEL32 import pass-through thunk.
extern void *impSetErrorMode[];
unsigned long __declspec(naked) __stdcall SetErrorMode(void *a)
{
    __asm { jmp dword ptr [impSetErrorMode] }
}
