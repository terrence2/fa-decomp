// _AIL_set_sample_loop_count@8 @ rva 0xd35ac (6 B) — AIL_set_sample_loop_count (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_sample_loop_count[];
unsigned long __declspec(naked) __stdcall AIL_set_sample_loop_count(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_sample_loop_count] }
}
