// _AIL_set_XMIDI_master_volume@8 @ rva 0xd354c (6 B) — AIL_set_XMIDI_master_volume (Miles AIL) sound import pass-through thunk.
extern void *impAIL_set_XMIDI_master_volume[];
unsigned long __declspec(naked) __stdcall AIL_set_XMIDI_master_volume(void *a0, void *a1)
{
    __asm { jmp dword ptr [impAIL_set_XMIDI_master_volume] }
}
