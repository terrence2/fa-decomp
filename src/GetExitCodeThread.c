// _GetExitCodeThread@8 @ rva 0xd33d2 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetExitCodeThread[];
unsigned long __declspec(naked) __stdcall GetExitCodeThread(void *a, void *b)
{
    __asm { jmp dword ptr [impGetExitCodeThread] }
}
