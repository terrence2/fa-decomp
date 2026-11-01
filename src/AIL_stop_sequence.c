// _AIL_stop_sequence@4 @ rva 0xd358e (6 B) — AIL_stop_sequence (Miles AIL) sound import pass-through thunk.
extern void *impAIL_stop_sequence[];
unsigned long __declspec(naked) __stdcall AIL_stop_sequence(void *a0)
{
    __asm { jmp dword ptr [impAIL_stop_sequence] }
}
