// _AIL_stop_timer@4 @ rva 0xd3522 (6 B) — AIL_stop_timer (Miles AIL) sound import pass-through thunk.
extern void *impAIL_stop_timer[];
unsigned long __declspec(naked) __stdcall AIL_stop_timer(void *a0)
{
    __asm { jmp dword ptr [impAIL_stop_timer] }
}
