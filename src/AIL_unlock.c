// _AIL_unlock@0 @ rva 0xd3546 (6 B) — AIL_unlock (Miles AIL) sound import pass-through thunk.
extern void *impAIL_unlock[];
unsigned long __declspec(naked) __stdcall AIL_unlock()
{
    __asm { jmp dword ptr [impAIL_unlock] }
}
