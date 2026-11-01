// @RMNotify@4 @ rva 0xa3c50 (64 B) — FA asm (fastcall, id in ecx): 53/a0
//   <resList+0x67ec>/84 c0/74 2b/b8 <resList+0> (table start as imm32)/bb 02
//   (ebx holds the 2 mask, not an immediate)/8a 10/84 d2/74 0c/84 58 0e
//   (test [rec+0xe],bl — reg not imm)/8b 50 0f (mov edx INTERLEAVED between
//   the test and its je)/74 04/3b d1/74 0c/83 c0 13/3d <resList+0x67e8>/
//   72 e4/5b c3/c6 00 00/5b c3.  Naked-asm escape: the reg-held mask
//   (test mem,bl requires CL to spend a byte in bl), the interleave and the
//   manual 53/5b (naked asm does no auto-save) are unsteerable.  Records are
//   0x13 B; resList +0x67e8 = end-of-table, +0x67ec = the enable byte past
//   it.  Probe build/w4probe/w19_rmnotify_v1.obj — exact.
extern char rmResListLo[];    /* ?resList@@3PAURES_LIST@@A base (0x4ff720) */
extern char rmResListEnd[];   /* +0x67e8 */
extern char rmResEnabled[];   /* +0x67ec */

__declspec(naked) void __fastcall RMNotify_f(long id)
{
    __asm {
        push ebx
        mov al, rmResEnabled
        test al, al
        je Done
        mov eax, offset rmResListLo
        mov ebx, 2
    Lp:
        mov dl, [eax]
        test dl, dl
        je Skip
        test byte ptr [eax+0xe], bl
        mov edx, [eax+0xf]
        je Skip
        cmp edx, ecx
        je Found
    Skip:
        add eax, 0x13
        cmp eax, offset rmResListEnd
        jb Lp
        pop ebx
        ret
    Found:
        mov byte ptr [eax], 0
    Done:
        pop ebx
        ret
    }
}