// _GetLogicalDrives@0 @ rva 0xd3354 (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetLogicalDrives[];
unsigned long __declspec(naked) __stdcall GetLogicalDrives(void)
{
    __asm { jmp dword ptr [impGetLogicalDrives] }
}
