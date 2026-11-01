// _CloseHandle@4 @ rva 0xd3390 (6 B) — KERNEL32 import pass-through thunk.
extern void *impCloseHandle[];
unsigned long __declspec(naked) __stdcall CloseHandle(void *a)
{
    __asm { jmp dword ptr [impCloseHandle] }
}
