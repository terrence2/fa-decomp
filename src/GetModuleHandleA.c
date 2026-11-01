// _GetModuleHandleA@4 @ rva 0xe4dc6 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetModuleHandleA[];
void __declspec(naked) __stdcall GetModuleHandleA(void)
{
    __asm { jmp dword ptr [impGetModuleHandleA] }
}
