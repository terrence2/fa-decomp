// @FPSPrint@4 @ rva 0x84ef0 (32 B) — Sprintf(fmt from ?noTimerSleep@@3JA+0x10,
//   _currentT+0x14) via esi-kept param, then a thiscall into the next chunk
//   $FA$_t_484f10 (e8 02 00 00 00) whose ret lands on the 5e/c3 tail that
//   restores esi. Needs naked asm: the param never leaves esi (probe d144).
extern long fpspT14;
extern char fpspFmt[];
extern int __cdecl Sprintf(char *fmt, ...);
extern void fpspTail(void);
__declspec(naked) void FPSPrint_q(void)
{
    __asm {
        push esi
        mov  eax, dword ptr [fpspT14]
        mov  esi, ecx
        push eax
        push offset fpspFmt
        push esi
        call Sprintf
        add  esp, 0xc
        mov  ecx, esi
        call fpspTail
        pop  esi
        ret
    }
}
