// _TlsSetValue@8 @ rva 0xe4e02 (6 B) - KERNEL32 import pass-through thunk.
extern void *impTlsSetValue[];
void __declspec(naked) __stdcall TlsSetValue(void)
{
    __asm { jmp dword ptr [impTlsSetValue] }
}
