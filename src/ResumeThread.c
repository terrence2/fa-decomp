// _ResumeThread@4 @ rva 0xd33e4 (6 B) — KERNEL32 import pass-through thunk.
extern void *impResumeThread[];
unsigned long __declspec(naked) __stdcall ResumeThread(void *a)
{
    __asm { jmp dword ptr [impResumeThread] }
}
