// _IsValidLocale@8 @ rva 0xe4e86 (6 B) - KERNEL32 import pass-through thunk.
extern void *impIsValidLocale[];
void __declspec(naked) __stdcall IsValidLocale(void)
{
    __asm { jmp dword ptr [impIsValidLocale] }
}
