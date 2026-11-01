// _GetLocaleInfoW@16 @ rva 0xe4ec8 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetLocaleInfoW[];
void __declspec(naked) __stdcall GetLocaleInfoW(void)
{
    __asm { jmp dword ptr [impGetLocaleInfoW] }
}
