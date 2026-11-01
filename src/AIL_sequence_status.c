// _AIL_sequence_status@4 @ rva 0xd3558 (6 B) — AIL_sequence_status (Miles AIL) sound import pass-through thunk.
extern void *impAIL_sequence_status[];
unsigned long __declspec(naked) __stdcall AIL_sequence_status(void *a0)
{
    __asm { jmp dword ptr [impAIL_sequence_status] }
}
