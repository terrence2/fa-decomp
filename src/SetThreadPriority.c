// _SetThreadPriority@8 @ rva 0xd335a (6 B) — KERNEL32 import pass-through thunk.
extern void *impSetThreadPriority[];
unsigned long __declspec(naked) __stdcall SetThreadPriority(void *a, void *b)
{
    __asm { jmp dword ptr [impSetThreadPriority] }
}
