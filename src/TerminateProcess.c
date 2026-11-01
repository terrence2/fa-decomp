// _TerminateProcess@8 @ rva 0xe4da2 (6 B) — TerminateProcess (KERNEL32) import pass-through thunk.
extern void *impTerminateProcess[];
unsigned long __declspec(naked) __stdcall TerminateProcess(void *a0, void *a1)
{
    __asm { jmp dword ptr [impTerminateProcess] }
}
