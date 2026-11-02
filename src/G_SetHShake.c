// @G_SetHShake@8 @ rva 0x97330 (62 B code + 2 B 8bff pad) — fastcall
// (hz=ecx, amp=edx) tick recompute with esi as scratch, shared epilogue at
// the end (jl/jle jump into pop esi) and the eax t|0x10 short path storing
// _hShakeTicks AFTER the pop (a3).  asm: mov hShakeTicks,eax -> A3 store;
// amp/4 signed = cdq/and edx,3/add/sar 2.
extern long hShakeTicks;                /* _hShakeTicks */
extern long hHzMod;                     /* _hHzMod */

__declspec(naked) void __fastcall G_SetHShake_q(int hz, int amp)
{
    __asm {
        push esi
        mov  eax, hShakeTicks
        mov  esi, hHzMod
        test eax, eax
        jle  Lb
        cmp  esi, ecx
        jl   Lexit
    Lb: test eax, eax
        jle  Lb2
        cmp  esi, ecx
        jne  Lb2
        or   eax, 10h
        pop  esi
        mov  hShakeTicks, eax
        ret
    Lb2:mov  eax, edx
        mov  hHzMod, ecx
        cdq
        and  edx, 3
        add  eax, edx
        sar  eax, 2
        mov  hShakeTicks, eax
    Lexit:
        pop  esi
        ret
    }
}