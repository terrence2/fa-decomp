// _AIL_set_sample_playback_rate@8 @ rva 0xd35c4 (6 B) — AIL_set_sample_playback_rate (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_sample_playback_rate[];
unsigned long __declspec(naked) __stdcall AIL_set_sample_playback_rate(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_sample_playback_rate] }
}
