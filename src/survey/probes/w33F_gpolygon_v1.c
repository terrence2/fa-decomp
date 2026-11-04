// @G_Polygon@8 @ rva 0xc4de8 (60 B = 59 code + 1 pad "90") -- FA asm:
// fastcall (y in cx, x in edx, args pass through to callees):
//   push ebx/esi/edi/ebp / mov ds:__right+0x14,edx / mov esi,edx /
//   movzx ecx,cx / mov ds:__right+0x10,ecx / mov byte ds:__right+0x7c,0 /
//   cmp ds:_expandTerrain,0 / je L1 / call @G_SUPolygon@8+0x11b4 / L1:
//   call @G_SUPolygon@8+0x4cc / jae L2 / call @G_UPolygon@8 / L2:
//   pop ebp/edi/esi/ebx / ret / nop pad.
// Naked-asm escape: the callee-args-pass-through-in-ecx/edx chain and the
// CF-conditional jae after a call (no test between) are patch-hostile C.
extern void gsup1(void);
extern void gsup2(void);
extern void gup(void);
extern char right[];
extern int expandTerrain;

void __declspec(naked) __fastcall G_Polygon(short y, int x)
{
    __asm {
        push ebx
        push esi
        push edi
        push ebp
        mov dword ptr [right+0x14], edx
        mov esi, edx
        movzx ecx, cx
        mov dword ptr [right+0x10], ecx
        mov byte ptr [right+0x7c], 0
        cmp dword ptr [expandTerrain], 0
        je L1
        call gsup1
    L1:
        call gsup2
        jae L2
        call gup
    L2:
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
    }
}