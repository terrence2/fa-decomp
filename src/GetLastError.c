// _GetLastError@0 @ rva 0xe4db4 (6 B) — GetLastError (KERNEL32) import pass-through thunk.
extern void *impGetLastError[];
unsigned long __declspec(naked) __stdcall GetLastError()
{
    __asm { jmp dword ptr [impGetLastError] }
}
