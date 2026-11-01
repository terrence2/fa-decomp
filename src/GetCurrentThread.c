// _GetCurrentThread@0 @ rva 0xd3360 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetCurrentThread[];
unsigned long __declspec(naked) __stdcall GetCurrentThread(void)
{
    __asm { jmp dword ptr [impGetCurrentThread] }
}
