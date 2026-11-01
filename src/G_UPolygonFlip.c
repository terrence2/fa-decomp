// @G_UPolygonFlip@8 @ rva 0x96620 (64 B) — same shape as G_PolygonFlip
// (push esi / a0 [cFillType] / push edi / mov esi,ecx / mov edi,edx / test al /
// je pass / a1 [effects] / a9 0x10000 / je pass / call @G_FloatFlatFlip@8 /
// pops+ret / pass: edx,edi reload + call @G_Flip@8 + reload + call @G_UPolygon@8 /
// pops+ret). asm escape per wave-3 cookbook: 0-arg fastcall passthrough can't
// be typed in C; a0/a9 MASM-only moffs/imm-test forms (probe
// b17c_gupolygonflip byte-exact; sibling of G_PolygonFlip probe).
extern char cFillType[];
extern char effects[];
extern int gFloatFlatFlip(void);  /* map _gFloatFlatFlip=@G_FloatFlatFlip@8 */
extern int gFlip(void);           /* map _gFlip=@G_Flip@8 */
extern int gUPolygon(void);       /* map _gUPolygon=@G_UPolygon@8 */

__declspec(naked) void __fastcall G_UPolygonFlip(void)
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
        call gUPolygon
        pop edi
        pop esi
        ret
    }
}