// @G_SPolygonFlip@8 @ rva 0x96660 — push esi / push edi / mov esi,edx /
//   mov edi,ecx / call @G_Flip@8 / mov edx,esi / mov ecx,edi / call
//   @G_SPolygon@8 / pop edi / pop esi / ret. The pure-C two-call forwarder
//   (probe d21) spills with the opposite esi/edi pairing (CL keeps 2nd arg
//   in edi), so the leaf is inline __asm. Inline asm auto-saves esi/edi —
//   the leading push esi/push edi and trailing pops are compiler-emitted
//   (probe d35 exact modulo rel32).
extern void __fastcall G_Flip(int a, int b);
extern void __fastcall G_SPolygon(int a, int b);

void G_SPolygonFlip_q(void)
{
    __asm {
        mov     esi, edx
        mov     edi, ecx
        call    G_Flip
        mov     edx, esi
        mov     ecx, edi
        call    G_SPolygon
    }
}
