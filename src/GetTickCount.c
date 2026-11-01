// _GetTickCount@0 @ rva 0xd3468 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetTickCount[];
unsigned long __declspec(naked) __stdcall GetTickCount(void)
{
    __asm { jmp dword ptr [impGetTickCount] }
}
