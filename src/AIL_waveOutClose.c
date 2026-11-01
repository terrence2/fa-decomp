// _AIL_waveOutClose@4 @ rva 0xd357c (6 B) — AIL_waveOutClose (Miles AIL) sound import pass-through thunk.
extern void *impAIL_waveOutClose[];
unsigned long __declspec(naked) __stdcall AIL_waveOutClose(void *a0)
{
    __asm { jmp dword ptr [impAIL_waveOutClose] }
}
