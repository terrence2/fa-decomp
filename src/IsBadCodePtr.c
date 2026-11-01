// _IsBadCodePtr@4 @ rva 0xe4eb0 (6 B) - KERNEL32 import pass-through thunk.
extern void *impIsBadCodePtr[];
void __declspec(naked) __stdcall IsBadCodePtr(void)
{
    __asm { jmp dword ptr [impIsBadCodePtr] }
}
