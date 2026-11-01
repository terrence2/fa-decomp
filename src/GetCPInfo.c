// _GetCPInfo@8 @ rva 0xe4e26 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetCPInfo[];
void __declspec(naked) __stdcall GetCPInfo(void)
{
    __asm { jmp dword ptr [impGetCPInfo] }
}
