// _GetStringTypeW@16 @ rva 0xe4e80 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetStringTypeW[];
void __declspec(naked) __stdcall GetStringTypeW(void)
{
    __asm { jmp dword ptr [impGetStringTypeW] }
}
