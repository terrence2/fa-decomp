// _HeapCreate@12 @ rva 0xe4e74 (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapCreate[];
void __declspec(naked) __stdcall HeapCreate(void)
{
    __asm { jmp dword ptr [impHeapCreate] }
}
