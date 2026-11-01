// _AIL_lock@0 @ rva 0xd3552 (6 B) — AIL_lock (Miles AIL) sound import pass-through thunk.
extern void *impAIL_lock[];
unsigned long __declspec(naked) __stdcall AIL_lock()
{
    __asm { jmp dword ptr [impAIL_lock] }
}
