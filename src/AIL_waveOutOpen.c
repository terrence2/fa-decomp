// _AIL_waveOutOpen@16 @ rva 0xd3564 (6 B) — AIL_waveOutOpen (Miles AIL) sound import pass-through thunk.
extern void *impAIL_waveOutOpen[];
unsigned long __declspec(naked) __stdcall AIL_waveOutOpen(void *a0, void *a1, void *a2, void *a3)
{
    __asm { jmp dword ptr [impAIL_waveOutOpen] }
}
