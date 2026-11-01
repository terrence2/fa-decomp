// _GetCurrentThreadId@0 @ rva 0xd33c6 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetCurrentThreadId[];
unsigned long __declspec(naked) __stdcall GetCurrentThreadId(void)
{
    __asm { jmp dword ptr [impGetCurrentThreadId] }
}
