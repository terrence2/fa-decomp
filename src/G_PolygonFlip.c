// @G_PolygonFlip@8 @ rva 0x965e0 (64 B) — FA asm: push esi / a0 mov al,[cFillType]
// / push edi / mov esi,ecx / mov edi,edx / 84 c0 test al,al / je pass /
// a1 [effects] / a9 test eax,0x10000 / je pass / call @G_FloatFlatFlip@8 (the
// esi/edi spills are its fastcall args: 0-arg decl, ecx/edx left live) /
// pop edi / pop esi / ret / pass: mov edx,edi / mov ecx,esi / call @G_Flip@8 /
// mov edx,edi / mov ecx,esi / call @G_Polygon@8 / pop edi / pop esi / ret.
// asm escape (probe b17c_gpolygonflip byte-exact): the interleave push esi /
// mov al,[cFillType] / push edi is not schedulable from C, and the 0-arg
// fastcall escape (params passed straight through in ecx/edx, no spill in the
// take-path) has no C form. Moffs a0 + a9 imm-test forms are MASM-only.
// cFillType/effects identity; maps alias the three @-decorated callees.
extern char cFillType[];
extern char effects[];
extern int gFloatFlatFlip(void);  /* map _gFloatFlatFlip=@G_FloatFlatFlip@8 */
extern int gFlip(void);           /* map _gFlip=@G_Flip@8 */
extern int gPolygon(void);        /* map _gPolygon=@G_Polygon@8 */

__declspec(naked) void __fastcall G_PolygonFlip(void)
{
    __asm {
        push esi
        mov al, byte ptr [cFillType]
        push edi
        mov esi, ecx
        mov edi, edx
        test al, al
        je Lpass
        mov eax, dword ptr [effects]
        test eax, 10000h
        je Lpass
        call gFloatFlatFlip
        pop edi
        pop esi
        ret
Lpass:
        mov edx, edi
        mov ecx, esi
        call gFlip
        mov edx, edi
        mov ecx, esi
        call gPolygon
        pop edi
        pop esi
        ret
    }
}