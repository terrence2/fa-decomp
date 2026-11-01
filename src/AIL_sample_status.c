// _AIL_sample_status@4 @ rva 0xd3588 (6 B) — AIL_sample_status (Miles AIL) sound import pass-through thunk.
extern void *impAIL_sample_status[];
unsigned long __declspec(naked) __stdcall AIL_sample_status(void *a0)
{
    __asm { jmp dword ptr [impAIL_sample_status] }
}
