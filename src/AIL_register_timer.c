// _AIL_register_timer@4 @ rva 0xd3576 (6 B) — AIL_register_timer (Miles AIL) sound import pass-through thunk.
extern void *impAIL_register_timer[];
unsigned long __declspec(naked) __stdcall AIL_register_timer(void *a0)
{
    __asm { jmp dword ptr [impAIL_register_timer] }
}
