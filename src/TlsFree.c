// _TlsFree@4 @ rva 0xe4e0e (6 B) - KERNEL32 import pass-through thunk.
extern void *impTlsFree[];
void __declspec(naked) __stdcall TlsFree(void)
{
    __asm { jmp dword ptr [impTlsFree] }
}
