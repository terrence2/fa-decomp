// _GetOEMCP@0 @ rva 0xe4e32 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetOEMCP[];
void __declspec(naked) __stdcall GetOEMCP(void)
{
    __asm { jmp dword ptr [impGetOEMCP] }
}
