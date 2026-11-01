// _AIL_shutdown@0 @ rva 0xd351c (6 B) — AIL_shutdown (Miles AIL) sound import pass-through thunk.
extern void *impAIL_shutdown[];
unsigned long __declspec(naked) __stdcall AIL_shutdown()
{
    __asm { jmp dword ptr [impAIL_shutdown] }
}
