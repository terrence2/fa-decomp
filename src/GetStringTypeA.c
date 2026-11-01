// _GetStringTypeA@20 @ rva 0xe4e7a (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetStringTypeA[];
void __declspec(naked) __stdcall GetStringTypeA(void)
{
    __asm { jmp dword ptr [impGetStringTypeA] }
}
