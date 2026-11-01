// _AIL_init_sequence@12 @ rva 0xd353a (6 B) — AIL_init_sequence (Miles AIL) sound import pass-through thunk.
extern void *impAIL_init_sequence[];
unsigned long __declspec(naked) __stdcall AIL_init_sequence(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impAIL_init_sequence] }
}
