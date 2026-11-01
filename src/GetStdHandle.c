// _GetStdHandle@4 @ rva 0xe4e68 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetStdHandle[];
void __declspec(naked) __stdcall GetStdHandle(void)
{
    __asm { jmp dword ptr [impGetStdHandle] }
}
