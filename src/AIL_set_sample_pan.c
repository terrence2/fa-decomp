// _AIL_set_sample_pan@8 @ rva 0xd35b8 (6 B) — AIL_set_sample_pan (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_sample_pan[];
unsigned long __declspec(naked) __stdcall AIL_set_sample_pan(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_sample_pan] }
}
