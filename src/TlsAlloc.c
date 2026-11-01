// _TlsAlloc@0 @ rva 0xe4e08 (6 B) - KERNEL32 import pass-through thunk.
extern void *impTlsAlloc[];
void __declspec(naked) __stdcall TlsAlloc(void)
{
    __asm { jmp dword ptr [impTlsAlloc] }
}
