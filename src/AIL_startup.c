// _AIL_startup@0 @ rva 0xd3516 (6 B) — AIL_startup (Miles AIL) sound import pass-through thunk.
extern void *impAIL_startup[];
unsigned long __declspec(naked) __stdcall AIL_startup()
{
    __asm { jmp dword ptr [impAIL_startup] }
}
