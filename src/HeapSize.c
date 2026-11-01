// _HeapSize@12 @ rva 0xe4ee6 (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapSize[];
void __declspec(naked) __stdcall HeapSize(void)
{
    __asm { jmp dword ptr [impHeapSize] }
}
