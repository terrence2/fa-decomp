// _CTEval_canclimb @ rva 0x64540 — COMinSpeed()+0x4b <= *(curThing+0x34)>>8.
//   C keeps folding r+0x4b into lea ecx and never materializes the res/ebx
//   setle form (d49/d73) → inline __asm (d78 exact; CL auto-saves ebx).
extern char curThing[];
extern int COMinSpeed(void);

int CTEval_canclimb_q(void)
{
    __asm {
        call COMinSpeed
        xor  ebx, ebx
        add  eax, 0x4b
        mov  ecx, dword ptr [curThing+0x34]
        sar  ecx, 8
        cmp  eax, ecx
        setle bl
        mov  eax, ebx
    }
}
