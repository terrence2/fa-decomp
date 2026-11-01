// _AIL_start_sequence@4 @ rva 0xd352e (6 B) — AIL_start_sequence (Miles AIL) sound import pass-through thunk.
extern void *impAIL_start_sequence[];
unsigned long __declspec(naked) __stdcall AIL_start_sequence(void *a0)
{
    __asm { jmp dword ptr [impAIL_start_sequence] }
}
