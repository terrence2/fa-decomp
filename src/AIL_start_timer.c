// _AIL_start_timer@4 @ rva 0xd356a (6 B) — AIL_start_timer (Miles AIL) sound import pass-through thunk.
extern void *impAIL_start_timer[];
unsigned long __declspec(naked) __stdcall AIL_start_timer(void *a0)
{
    __asm { jmp dword ptr [impAIL_start_timer] }
}
