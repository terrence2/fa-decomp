// @MMShutdown@0 @ rva 0x35870 (64 B) — FA asm: push esi / mov al,<mm_init>/
//   test/je ret / xor esi,esi / loop: mov ecx,esi (fastcall id) / inc esi /
//   call @MMFreeAllId@4 / cmp esi,0x13 / jl loop / mov byte [mm_init],0 /
//   mov eax,<mm_handles> / test/je ret / push eax / call $FA$_t_4d4880 (the
//   CRT free() forwarder, same anchor fcAnchor_/ggFree/GFindCloseClean map
//   to) / add esp,4 / ret: pop esi / ret.  Frees ids 0..18 through
//   MMFreeAllId, drops the initialized flag, then frees the handle array.
//   v1 plain C: for-loop with fastcall id (param in ecx loaded from a shared
//   counter); CL's fastcall-arg-in-ecx plan matched _ServicePlayer (wave 17
//   precedent).  Fallback naked asm if CL orders the inc after the call.
extern char mm_initialized;
extern void *mm_handles;
extern void __fastcall MMFreeAllId(long id);
extern void __cdecl mmFree(void *p);

void __fastcall MMShutdown(void)
{
    long i;
    if (!mm_initialized) return;
    for (i = 0; i < 0x13; i++) {
        MMFreeAllId(i);
    }
    mm_initialized = 0;
    if (mm_handles)
        mmFree(mm_handles);
}