// _AIL_start_sample@4 @ rva 0xd359a (6 B) — AIL_start_sample (Miles AIL) sound import pass-through thunk.
extern void *impAIL_start_sample[];
unsigned long __declspec(naked) __stdcall AIL_start_sample(void *a0)
{
    __asm { jmp dword ptr [impAIL_start_sample] }
}
