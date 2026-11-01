// _AIL_end_sample@4 @ rva 0xd3582 (6 B) — AIL_end_sample (Miles AIL) sound import pass-through thunk.
extern void *impAIL_end_sample[];
unsigned long __declspec(naked) __stdcall AIL_end_sample(void *a0)
{
    __asm { jmp dword ptr [impAIL_end_sample] }
}
