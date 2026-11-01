// _IsBadWritePtr@8 @ rva 0xe4eaa (6 B) - KERNEL32 import pass-through thunk.
extern void *impIsBadWritePtr[];
void __declspec(naked) __stdcall IsBadWritePtr(void)
{
    __asm { jmp dword ptr [impIsBadWritePtr] }
}
