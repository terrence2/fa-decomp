// _GetLocaleInfoA@16 @ rva 0xe4ec2 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetLocaleInfoA[];
void __declspec(naked) __stdcall GetLocaleInfoA(void)
{
    __asm { jmp dword ptr [impGetLocaleInfoA] }
}
