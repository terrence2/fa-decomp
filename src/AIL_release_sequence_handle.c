// _AIL_release_sequence_handle@4 @ rva 0xd3534 (6 B) — AIL_release_sequence_handle (Miles AIL) sound import pass-through thunk.
extern void *impAIL_release_sequence_handle[];
unsigned long __declspec(naked) __stdcall AIL_release_sequence_handle(void *a0)
{
    __asm { jmp dword ptr [impAIL_release_sequence_handle] }
}
