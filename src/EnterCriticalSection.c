// _EnterCriticalSection@4 @ rva 0xd3348 (6 B) — KERNEL32 import pass-through thunk.
extern void *impEnterCriticalSection[];
unsigned long __declspec(naked) __stdcall EnterCriticalSection(void *a)
{
    __asm { jmp dword ptr [impEnterCriticalSection] }
}
