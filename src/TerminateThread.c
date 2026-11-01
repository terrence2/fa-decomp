// _TerminateThread@8 @ rva 0xd33ea (6 B) — KERNEL32 import pass-through thunk.
extern void *impTerminateThread[];
unsigned long __declspec(naked) __stdcall TerminateThread(void *a, void *b)
{
    __asm { jmp dword ptr [impTerminateThread] }
}
