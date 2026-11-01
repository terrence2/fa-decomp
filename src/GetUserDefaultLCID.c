// _GetUserDefaultLCID@0 @ rva 0xe4e92 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetUserDefaultLCID[];
void __declspec(naked) __stdcall GetUserDefaultLCID(void)
{
    __asm { jmp dword ptr [impGetUserDefaultLCID] }
}
