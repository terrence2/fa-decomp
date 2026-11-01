// _GetCurrentProcess@0 @ rva 0xe4da8 (6 B) — GetCurrentProcess (KERNEL32) import pass-through thunk.
extern void *impGetCurrentProcess[];
unsigned long __declspec(naked) __stdcall GetCurrentProcess()
{
    __asm { jmp dword ptr [impGetCurrentProcess] }
}
