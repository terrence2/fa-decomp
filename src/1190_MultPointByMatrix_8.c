// _MultPointByMatrix@8 @ rva 0xd26cc (44 B, gap chunk, no FPO) — int
// __stdcall MultPointByMatrix(void *dst, void *mtx): x87-family vector
// transform: save ebx/esi/edi + FRAME ebp as a 4th pushed value (the core
// at ecode_pnt+0x84 walks the caller frame with ebp), esi=arg1, replace
// ebp with arg2 for the call, pop frame back, then dst = *(short*)[dst+8]
// ... store bx/cx/di to [dst+0/2/4] (pop ebp restores the frame pointer so
// [ebp+8] re-reads arg1). The deliberate ebp clobber around the call and
// the word stores make this asm-only.
extern void mpbmCore(void);          /* ecode_pnt + 0x84 */

int __declspec(naked) __stdcall MultPointByMatrixQ(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        push ebx
        push esi
        push edi
        push ebp
        mov  esi, dword ptr [ebp+0x8]
        mov  ebp, dword ptr [ebp+0xc]
        call mpbmCore
        pop  ebp
        mov  ebp, dword ptr [ebp+0x8]
        mov  word ptr [ebp], bx
        mov  word ptr [ebp+0x2], cx
        mov  word ptr [ebp+0x4], di
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        ret  0x8
    }
}