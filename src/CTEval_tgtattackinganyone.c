// _CTEval_tgtattackinganyone @ rva 0x64090 (64 B) — FA asm: 66 83 3d
//   <_serviceTicks+0x20>,0 (word gate)/74 2c/a0 <+0xe8>/84 c0/74 23/
//   a1 <+0xf4>/8a 88 <[tgt]+0xe3>/80 f9 20/72 10/66 83 b8 <[tgt]+0xee>,0
//   (reg-relative word cmp, 8 B)/74 06/b8 01/c3/33 c0 c3/33 c0 c3.  Naked-asm
//   escape: the moffs byte loads, the mov cl,[eax+0xe3] reg plan and the two
//   separate ret0 blocks (jb and je to a second xor/ret block past the first)
//   are FA codegen shapes CL cannot hold.  Probe
//   build/w4probe/w19_tgtattack_v1.obj — exact (serviceTicks is the identity
//   chunk name; CL bakes +0x20/+0xe8/+0xf4 into the disp contents).
extern char serviceTicks[];

__declspec(naked) long CTEval_tgtattackinganyone(void)
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
        cmp word ptr [eax+0xee], 0
        je R0A
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