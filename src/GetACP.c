// _GetACP@0 @ rva 0xe4e2c (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetACP[];
void __declspec(naked) __stdcall GetACP(void)
{
    __asm { jmp dword ptr [impGetACP] }
}
