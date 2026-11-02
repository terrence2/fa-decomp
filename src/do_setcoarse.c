// do_setcoarse @ rva 0xd069c (28 B, gap chunk, no FPO) — interp do-handler:
// read word at [esi] (zero-extended via movzx eax), esi += 2, store to the
// _coarse global (a3 moffs store), read next word -> movzx bl, tail-dispatch
// jmp dword ptr [ebx*2 + vector_table] (base-less sib-5d; EBX = cmd byte).
// Ends in the jump — no ret. Naked asm escape (esi/ebx interpreter
// register-state protocol).
extern int coarseG;                  /* _coarse */
extern void *setVT[];                /* vector_table */

void __declspec(naked) do_setcoarse_q(void)
{
    __asm {
        movzx eax, word ptr [esi]
        add  esi, 0x2
        mov  coarseG, eax
        mov  ax, word ptr [esi]
        lea  esi, [esi+0x2]
        movzx ebx, al
        jmp  dword ptr setVT[ebx*2]
    }
}