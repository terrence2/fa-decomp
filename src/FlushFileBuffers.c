// _FlushFileBuffers@4 @ rva 0xe4e38 (6 B) - KERNEL32 import pass-through thunk.
extern void *impFlushFileBuffers[];
void __declspec(naked) __stdcall FlushFileBuffers(void)
{
    __asm { jmp dword ptr [impFlushFileBuffers] }
}
