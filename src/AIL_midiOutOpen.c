// _AIL_midiOutOpen@12 @ rva 0xd350a (6 B) — AIL_midiOutOpen (Miles AIL) sound import pass-through thunk.
extern void *impAIL_midiOutOpen[];
unsigned long __declspec(naked) __stdcall AIL_midiOutOpen(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impAIL_midiOutOpen] }
}
