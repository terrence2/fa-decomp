// _HeapAlloc@12 @ rva 0xe4e20 (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapAlloc[];
void __declspec(naked) __stdcall HeapAlloc(void)
{
    __asm { jmp dword ptr [impHeapAlloc] }
}
