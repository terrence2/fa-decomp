// _AIL_midiOutClose@4 @ rva 0xd3528 (6 B) — AIL_midiOutClose (Miles AIL) sound import pass-through thunk.
extern void *impAIL_midiOutClose[];
unsigned long __declspec(naked) __stdcall AIL_midiOutClose(void *a0)
{
    __asm { jmp dword ptr [impAIL_midiOutClose] }
}
