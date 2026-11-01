// _GetThreadPriority@4 @ rva 0xd3366 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetThreadPriority[];
unsigned long __declspec(naked) __stdcall GetThreadPriority(void *a)
{
    __asm { jmp dword ptr [impGetThreadPriority] }
}
