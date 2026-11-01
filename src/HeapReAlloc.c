// _HeapReAlloc@16 @ rva 0xe4eda (6 B) - KERNEL32 import pass-through thunk.
extern void *impHeapReAlloc[];
void __declspec(naked) __stdcall HeapReAlloc(void)
{
    __asm { jmp dword ptr [impHeapReAlloc] }
}
