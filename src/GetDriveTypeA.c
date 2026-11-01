// _GetDriveTypeA@4 @ rva 0xd334e (6 B) — KERNEL32 import pass-through thunk.
extern void *impGetDriveTypeA[];
unsigned long __declspec(naked) __stdcall GetDriveTypeA(void *a)
{
    __asm { jmp dword ptr [impGetDriveTypeA] }
}
