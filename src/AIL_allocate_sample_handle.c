// _AIL_allocate_sample_handle@4 @ rva 0xd355e (6 B) — AIL_allocate_sample_handle (Miles AIL) sound import pass-through thunk.
extern void *impAIL_allocate_sample_handle[];
unsigned long __declspec(naked) __stdcall AIL_allocate_sample_handle(void *a0)
{
    __asm { jmp dword ptr [impAIL_allocate_sample_handle] }
}
