// _TlsGetValue@4 @ rva 0xe4e1a (6 B) - KERNEL32 import pass-through thunk.
extern void *impTlsGetValue[];
void __declspec(naked) __stdcall TlsGetValue(void)
{
    __asm { jmp dword ptr [impTlsGetValue] }
}
