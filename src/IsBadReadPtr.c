// _IsBadReadPtr@8 @ rva 0xe4ea4 (6 B) - KERNEL32 import pass-through thunk.
extern void *impIsBadReadPtr[];
void __declspec(naked) __stdcall IsBadReadPtr(void)
{
    __asm { jmp dword ptr [impIsBadReadPtr] }
}
