// _LeaveCriticalSection@4 @ rva 0xd3342 (6 B) — KERNEL32 import
// pass-through thunk.
extern void *impLeaveCS2[];
void __declspec(naked) __stdcall LeaveCriticalSection(void *cs)
{
    __asm { jmp dword ptr [impLeaveCS2] }
}
