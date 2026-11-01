// _SetStdHandle@8 @ rva 0xe4e98 (6 B) - KERNEL32 import pass-through thunk.
extern void *impSetStdHandle[];
void __declspec(naked) __stdcall SetStdHandle(void)
{
    __asm { jmp dword ptr [impSetStdHandle] }
}
