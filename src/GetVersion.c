// _GetVersion@0 @ rva 0xe4dd8 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetVersion[];
void __declspec(naked) __stdcall GetVersion(void)
{
    __asm { jmp dword ptr [impGetVersion] }
}
