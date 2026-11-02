// ?CleanCobra@@YAGPAUGlobalData@@@Z @ rva 0x6a2b0 (48 B) — cdecl
// ushort(void*). FA: push esi; esi=[esp+8](gd); mov ax,[esi+0xf2] (lib
// handle word — push carries stale uppers, callee is ushort-formal
// _LibClose); push eax / call _LibClose; add esp,4; mov ecx,[esi+0xea];
// call @MMFreePtr@4; xor ax,ax; pop esi; ret.
extern char __cdecl LibClose(unsigned short a);   /* _LibClose identity */
extern void __fastcall MMFreePtr(void *p);        /* @MMFreePtr@4 */

unsigned short __cdecl CleanCobra(void *gd)
{
    LibClose(*(unsigned short *)((char *)gd + 0xf2));
    MMFreePtr((void *)*(unsigned long *)((char *)gd + 0xea));
    return 0;
}