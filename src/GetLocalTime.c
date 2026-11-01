// _GetLocalTime@4 @ rva 0xd341a (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetLocalTime[];
unsigned long __declspec(naked) __stdcall GetLocalTime(void *a)
{
    __asm { jmp dword ptr [impGetLocalTime] }
}
