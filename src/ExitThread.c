// _ExitThread@4 @ rva 0xd33b4 (6 B) — KERNEL32 import pass-through thunk.
extern void *impExitThread[];
unsigned long __declspec(naked) __stdcall ExitThread(void *a)
{
    __asm { jmp dword ptr [impExitThread] }
}
