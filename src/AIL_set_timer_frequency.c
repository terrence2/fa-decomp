// _AIL_set_timer_frequency@8 @ rva 0xd3570 (6 B) — AIL_set_timer_frequency (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_timer_frequency[];
unsigned long __declspec(naked) __stdcall AIL_set_timer_frequency(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_timer_frequency] }
}
