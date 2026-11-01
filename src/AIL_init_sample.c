// _AIL_init_sample@4 @ rva 0xd35b2 (6 B) — AIL_init_sample (Miles AIL) sound import pass-through thunk.
extern void *impAIL_init_sample[];
unsigned long __declspec(naked) __stdcall AIL_init_sample(void *a0)
{
    __asm { jmp dword ptr [impAIL_init_sample] }
}
