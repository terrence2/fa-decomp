// _ExitProcess@4 @ rva 0xd33ba (6 B) — KERNEL32 import pass-through thunk.
extern void *impExitProcess[];
unsigned long __declspec(naked) __stdcall ExitProcess(void *a)
{
    __asm { jmp dword ptr [impExitProcess] }
}
