// _CTEval_tgtattackingme @ rva 0x64050 (64 B) — FA asm: 66 83 3d
//   <_serviceTicks+0x20>,0 (word gate)/74 32/a0 <+0xe8>/84 c0/74 29/
//   a1 <+0xf4>/8a 88 <[tgt]+0xe3>/80 f9 20 (cmp cl,0x20)/72 16 (jb)/
//   66 8b 0d <_curId> (word load into cx)/66 39 88 <[tgt]+0xee> (cmp word
//   [tgt+0xee],cx)/75 06/b8 01/c3/33 c0 c3/33 c0 c3.  Naked-asm escape:
//   same family as _CTEval_tgtattackinganyone/_CTEval_alt/_CTEval_maxalt
//   (wave-19) — the moffs byte/word loads, the mov cl,[eax+0xe3] reg plan
//   and the stacked xor/ret exits are C-unreachable steering.  This twin
//   compares the target's [tgt+0xee] word against curId.  Probe
//   build/w4probe/b20f_CTEval_tgtattackingme.obj.obj — exact.
extern char serviceTicks[];
extern unsigned short curId;

__declspec(naked) long CTEval_tgtattackingme_q(void)
{
    __asm {
        cmp word ptr serviceTicks + 0x20, 0
        je R0
        mov al, byte ptr serviceTicks + 0xe8
        test al, al
        je R0
        mov eax, dword ptr serviceTicks + 0xf4
        mov cl, [eax+0xe3]
        cmp cl, 0x20
        jb R0A
        mov cx, word ptr curId
        cmp word ptr [eax+0xee], cx
        jne R0A
        mov eax, 1
        ret
    R0A:
        xor eax, eax
        ret
    R0:
        xor eax, eax
        ret
    }
}