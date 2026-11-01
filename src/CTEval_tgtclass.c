// _CTEval_tgtclass @ rva 0x64110 (48 B code + pad) — FA asm: 66 83 3d
//   <_serviceTicks+0x20>,0 (word gate)/75 03/33 c0 c3/a1 <+0xf4>/8b 48 05/
//   66 8b 41 0d (word load into ax, stale uppers kept)/f6 c4 c0 (test the
//   word's high byte against 0xc0)/74 17/8b 0d <+0xf4> (SECOND read via the
//   modrm form — first-read a1 / second-read 8b 0d canonicalization)/
//   8b 51 34/81 fa 00 0a 00 00/7d 06/b8 40 00 00 00/c3/25 ff ff 00 00 (the
//   and eax,0xffff zero-extend shared by both exits)/c3.  Naked-asm escape:
//   the mov ax,[ecx+0xd] non-movzx word load + test ah + final and is
//   C-unreachable steering (sibling _CTEval_alt/_CTEval_maxalt are the same
//   twins).  Probe build/w4probe/w19_tgtclass_v1.obj — exact.
extern char serviceTicks[];

__declspec(naked) long CTEval_tgtclass(void)
{
    __asm {
        cmp word ptr serviceTicks + 0x20, 0
        jne Cont
        xor eax, eax
        ret
    Cont:
        mov eax, dword ptr serviceTicks + 0xf4
        mov ecx, [eax+5]
        mov ax, [ecx+0xd]
        test ah, 0xc0
        je AndBlk
        mov ecx, dword ptr serviceTicks + 0xf4
        mov edx, [ecx+0x34]
        cmp edx, 0xa00
        jge AndBlk
        mov eax, 0x40
        ret
    AndBlk:
        and eax, 0xffff
        ret
    }
}