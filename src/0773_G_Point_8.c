// @G_Point@8 @ rva 0x95800 (48 B) — FA asm: 39 0d cmp [clipLeft],ecx
// (mem-first against fastcall param) / jg out / a1 [clipRight] / cmp eax,ecx /
// jl out / a1 [clipTop] / cmp eax,edx / jg out / a1 [clipBottom] (CSE'd return
// value: fail paths return whatever eax holds) / cmp eax,edx / jl out / tail
// jmp @G_UPoint@8 / out: ret.
// asm escape (probe b17c_gpoint_v5 byte-exact): every C formulation added a
// trailing `a1 [clipBottom]; c3` fail block after the tail jmp or restructured
// the frame (v1 ||-chain, v2 goto, v3 r-local, v4 comma-op all FAIL — CL needs
// the last cmp's operand load as the shared ret value, unreachable from C).
// clipLeft/Right/Top/Bottom identity; gUPoint -> @G_UPoint@8.
extern long clipLeft;
extern long clipRight;
extern long clipTop;
extern long clipBottom;
extern int gUPoint(int x, int y);   /* map _gUPoint=@G_UPoint@8 */

__declspec(naked) int __fastcall G_Point(int x, int y)
{
    __asm {
        cmp dword ptr [clipLeft], ecx
        jg Lret
        mov eax, dword ptr [clipRight]
        cmp eax, ecx
        jl Lret
        mov eax, dword ptr [clipTop]
        cmp eax, edx
        jg Lret
        mov eax, dword ptr [clipBottom]
        cmp eax, edx
        jl Lret
        jmp gUPoint
Lret:
        ret
    }
}