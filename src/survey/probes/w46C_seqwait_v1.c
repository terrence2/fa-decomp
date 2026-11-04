// Wave 46 batch C entry 5: _SEQwait @ rva 288576 (0x46640), 192 B.
// Waits on a sequence: strcmp(param,"all") inline-doubled compare; if "all",
// set seqList[7*curSeq]+3 flag byte; else walk the seqList name list
// (head +0x14, next at +0xe), and on match store node[+0xa] into
// seqList[7*curSeq]+0x20. FPO esp, locals=0, cbProlog=6 (push ebx,esi).
// Tail pad: 8d a4 24 00 00 00 00 (7 B).
extern char w46c_strn[];   /* ?valkyriesScore@@3DA+0x5dc = "all" */
extern short w46c_curseq;  /* ?curSeq@@3FA */
typedef struct { char x[8]; } W46C8;
extern W46C8 w46c_seqf[];  /* ?seqList@@3PAUSEQUENCE@@A+0x3  */
extern W46C8 w46c_seqh[];  /* ?seqList@@3PAUSEQUENCE@@A+0x14 */
extern W46C8 w46c_seqv[];  /* ?seqList@@3PAUSEQUENCE@@A+0x20 */

void __declspec(naked) SEQwait_q(void)
{
    __asm {
        mov  edx, [esp+4]
        push ebx
        push esi
        test edx, edx
        je   Lend
        mov  eax, edx
        mov  ecx, offset w46c_strn
    Lc1a:
        mov  bl, [eax]
        cmp  bl, [ecx]
        jne  Ld1a
        or   bl, bl
        je   Lz1a
        mov  bl, [eax+1]
        cmp  bl, [ecx+1]
        jne  Ld1a
        add  eax, 2
        add  ecx, 2
        or   bl, bl
        jne  Lc1a
    Lz1a:
        xor  eax, eax
        jmp  Lta
    Ld1a:
        sbb  eax, eax
        sbb  eax, -1
    Lta:
        test eax, eax
        movsx eax, word ptr w46c_curseq
        mov  ecx, eax
        jne  Lne
        shl  eax, 3
        pop  esi
        sub  eax, ecx
        pop  ebx
        mov  byte ptr w46c_seqf[eax*8], 1
        ret
    Lne:
        shl  eax, 3
        sub  eax, ecx
        mov  esi, dword ptr w46c_seqh[eax*8]
        test esi, esi
        je   Lend
    Lw:
        mov  eax, esi
        mov  ecx, edx
    Lc2a:
        mov  bl, [eax]
        cmp  bl, [ecx]
        jne  Ld2
        or   bl, bl
        je   Lz2
        mov  bl, [eax+1]
        cmp  bl, [ecx+1]
        jne  Ld2
        add  eax, 2
        add  ecx, 2
        or   bl, bl
        jne  Lc2a
    Lz2:
        xor  eax, eax
        jmp  Lta2
    Ld2:
        sbb  eax, eax
        sbb  eax, -1
    Lta2:
        test eax, eax
        je   Lst
        mov  esi, [esi+0xe]
        test esi, esi
        jne  Lw
        pop  esi
        pop  ebx
        ret
    Lst:
        movsx ecx, word ptr w46c_curseq
        mov  eax, [esi+0xa]
        mov  edx, ecx
        shl  ecx, 3
        sub  ecx, edx
        mov  dword ptr w46c_seqv[ecx*8], eax
    Lend:
        pop  esi
        pop  ebx
        ret
    }
}