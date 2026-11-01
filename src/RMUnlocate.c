// ?RMUnlocate@@YGXPAD@Z @ rva 0xa3810 (32 B) — FA asm:
//   mov ecx,[esp+4] / call @RMFind@4 (fastcall 1-arg: name travels in ecx) /
//   test eax,eax / je skip / mov byte ptr [eax],0 / skip: ret 4
// Fastcall extern declaration puts CL's arg load in ecx and the returned
// pointer is nulled out one byte: if (p) *p = 0. Plain C exact (probe
// b18c_RMUnlocate, only the call rel32 differs inside the reloc window).
extern char * __fastcall RMFind(char *name);

void __stdcall RMUnlocate(char *name)
{
    char *p = RMFind(name);
    if (p)
        *p = 0;
}
