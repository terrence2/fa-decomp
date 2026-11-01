// _HeapDestroy@4 @ rva 0xe4e6e (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapDestroy[];
void __declspec(naked) __stdcall HeapDestroy(void)
{
    __asm { jmp dword ptr [impHeapDestroy] }
}
