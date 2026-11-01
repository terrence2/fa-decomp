// _GetSystemInfo@4 @ rva 0xd336c (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetSystemInfo[];
unsigned long __declspec(naked) __stdcall GetSystemInfo(void *a)
{
    __asm { jmp dword ptr [impGetSystemInfo] }
}
