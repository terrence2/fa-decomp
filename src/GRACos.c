// @GRACos@4 @ rva 0xc9b50 (20 B, gap chunk) — FA fastcall glue (param in
// AX, a fixed-point angle): saves ebx/esi/edi/ebp, parks the param in BX,
// calls the sibling chunk "acos" (e8 rel32 into the very next chunk —
// layout.json names it acos), sign-extends the result CX. No C form
// (fastcall-in-AX param + no-arg fastcall-into-chunk call); naked asm with
// map _acosHelper=acos.
extern void acosHelper(void);

void __declspec(naked) GRACos(void)
{
    __asm {
        push ebx
        push esi
        push edi
        push ebp
        mov   bx, ax
        call  acosHelper
        movsx eax, cx
        pop   ebp
        pop   edi
        pop   esi
        pop   ebx
        ret
    }
}