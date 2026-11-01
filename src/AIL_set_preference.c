// _AIL_set_preference@8 @ rva 0xd3510 (6 B) — AIL_set_preference (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_preference[];
unsigned long __declspec(naked) __stdcall AIL_set_preference(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_preference] }
}
