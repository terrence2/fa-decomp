// ?CleanupCobra@@YAGPAUGlobalData@@@Z @ rva 0x6a6f0 (48 B) — cdecl
// ushort(void*); delegates to ?CleanAudio/?CleanVideo/?CleanCobra then
// ushort-0. FA: push esi; esi=[esp+8]; push esi/call/add esp,4 x3 with the
// final add AFTER xor ax,ax (ret-value first, stack cleanup last).
extern unsigned short __cdecl CleanAudio(void *gd);
extern unsigned short __cdecl CleanVideo(void *gd);
extern unsigned short __cdecl CleanCobra(void *gd);

unsigned short __cdecl CleanupCobra(void *gd)
{
    CleanAudio(gd);
    CleanVideo(gd);
    CleanCobra(gd);
    return 0;
}