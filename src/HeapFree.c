// _HeapFree@12 @ rva 0xe4dfc (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapFree[];
void __declspec(naked) __stdcall HeapFree(void)
{
    __asm { jmp dword ptr [impHeapFree] }
}
