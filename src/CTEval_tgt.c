// _CTEval_tgt @ rva 0x640d0 (64 B) — FA asm: 66 83 3d <_serviceTicks+0x20>,
//   0 (word gate)/74 2e/a1 <+0xf4>/8b 48 01 (mov ecx,[eax+1])/f6 c1 01
//   (test cl,1)/74 2e/a0 <+0xe8>/84 c0/74 12/a1 <+0xf4> (SECOND load)/
//   8a 88 <[tgt]+0xe3>/84 c9 (test cl)/75 03/33 c0 c3 (fallthrough ret0)/
//   b8 01 00 00 00/c3 (exit-1 block)/33 c0 c3 (early ret0 block)/
//   05 00 00 00 00 (tail pad).  Naked-asm escape: same CTEval twin family
//   (probe b19 family FAIL in plain C) — moffs loads, cl/ah byte tests and
//   the three exit blocks with shared targets are C-unreachable steering.
//   Probe build/w4probe/b20f_CTEval_tgt.obj — exact.
extern char serviceTicks[];

__declspec(naked) long CTEval_tgt_q(void)
{
    __asm {
        cmp word ptr serviceTicks + 0x20, 0
        je R0
        mov eax, dword ptr serviceTicks + 0xf4
        mov ecx, [eax+1]
        test cl, 1
        je R0
        mov al, byte ptr serviceTicks + 0xe8
        test al, al
        je R1
        mov eax, dword ptr serviceTicks + 0xf4
        mov cl, [eax+0xe3]
        test cl, cl
        jne R1
        xor eax, eax
        ret
    R1:
        mov eax, 1
        ret
    R0:
        xor eax, eax
        ret
    }
}