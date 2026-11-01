// _SuspendThread@4 @ rva 0xd33c0 (6 B) — KERNEL32 import pass-through thunk.
extern void *impSuspendThread[];
unsigned long __declspec(naked) __stdcall SuspendThread(void *a)
{
    __asm { jmp dword ptr [impSuspendThread] }
}
