// @G_SetVShake@8 @ rva 0x97370 — mirror of G_SetHShake@8 (0x97330) for the
// vertical pair _vShakeTicks/_vHzMod; the only structural diff is the first
// guard written the OTHER way round (cmp ecx,esi / jg — i.e. C said
// hz > h, not h < hz, a source-tell twin polarity).  Same A3 store / shared
// epilogue plan as the H twin.
extern long vShakeTicks;                /* _vShakeTicks */
extern long vHzMod;                     /* _vHzMod */

__declspec(naked) void __fastcall G_SetVShake_q(int hz, int amp)
{
    __asm {
        push esi
        mov  eax, vShakeTicks
        mov  esi, vHzMod
        test eax, eax
        jle  Lb
        cmp  ecx, esi
        jg   Lexit
    Lb: test eax, eax
        jle  Lb2
        cmp  ecx, esi
        jne  Lb2
        or   eax, 10h
        pop  esi
        mov  vShakeTicks, eax
        ret
    Lb2:mov  eax, edx
        mov  vHzMod, ecx
        cdq
        and  edx, 3
        add  eax, edx
        sar  eax, 2
        mov  vShakeTicks, eax
    Lexit:
        pop  esi
        ret
    }
}