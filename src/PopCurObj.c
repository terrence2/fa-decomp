// _PopCurObj@0 @ rva 0x61be0 (48 B) — FA asm: e8 @PutCurObj@0/a1 <ccp+
//   0x1c>/66 8b 0c 45 <ccp+0x6> (word load, scale-1 ecx index = PutCurObj's
//   call contract, no reload)/48/66 85 c9/a3 <+0x1c>/74.. /e9 @GetCurObj@4
//   or 66 c7 05 <_curId> 0000.  Inline-asm escape: MASM cannot emit the
//   scale-1 sib-45 form from the stale call-contract ecx (5 spellings all
//   collapse to 66 8b 89/0d — probe b17_sib_*.c), and no C variable can
//   live in ecx with no load (FA's own sib-45 precedent _ServicePlayer@0
//   pre-zeroes with 33 c9).  We emit CL's 66 8b 89 form and fitobj-patch
//   the modrm byte: patch "0xc,1,0c45" (batch_b entry) turns it into FA's
//   66 8b 0c 45, shifting the disp reloc to @0xe.  Probe
//   build/w4probe/b17_popcurobj_v2.c + fit run: exact modulo fixup dwords.

extern unsigned short curId;
extern char correctChainPlacement[];

extern void __fastcall PutCurObj(void);
extern void __fastcall GetCurObj(unsigned short id);

void PopCurObj(void) {
    __asm {
        call PutCurObj
        mov eax, dword ptr [correctChainPlacement + 0x1c]
        mov cx, word ptr correctChainPlacement[ecx*1 + 6]
        dec eax
        test cx, cx
        mov dword ptr [correctChainPlacement + 0x1c], eax
        je Lzero
        jmp GetCurObj
    Lzero:
        mov word ptr [curId], 0
    }
}