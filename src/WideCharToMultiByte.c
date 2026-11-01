// _WideCharToMultiByte@32 @ rva 0xe4df0 (6 B) - KERNEL32 import pass-through thunk.
extern void *impWideCharToMultiByte[];
void __declspec(naked) __stdcall WideCharToMultiByte(void)
{
    __asm { jmp dword ptr [impWideCharToMultiByte] }
}
