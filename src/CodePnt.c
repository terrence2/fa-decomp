// _CodePnt@12 @ rva 0xcb608 (24 B, gap chunk) — stdcall 3-arg register-
// contract thunk (the BGA/CTB driver convention): push ebp/mov ebp,esp
// frame, then the stack args go into the callee's registers (bx=arg1,
// cx=arg2, bp=arg3 — NOTE bp is overwritten by the frame-register load),
// tail-call code_pnt (8 B ahead), pop ebp, ret 12. Loading bp kills the
// frame so nothing can unwind normally — naked asm with explicit ret 12.
extern void code_pnt(void);

void __declspec(naked) __stdcall CodePnt(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        mov  bx, word ptr [ebp+8]
        mov  cx, word ptr [ebp+0xc]
        mov  bp, word ptr [ebp+0x10]
        call code_pnt
        pop  ebp
        ret 12
    }
}