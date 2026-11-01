// _AIL_set_sample_type@12 @ rva 0xd35a0 (6 B) — AIL_set_sample_type (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_sample_type[];
unsigned long __declspec(naked) __stdcall AIL_set_sample_type(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impAIL_set_sample_type] }
}
