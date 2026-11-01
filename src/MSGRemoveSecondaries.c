// @MSGRemoveSecondaries@4 @ rva 0x18790 (64 B) — FA asm: bf <lwb+0xf0>/
//   33 d2/66 83 78 06 ff ff/74.. (scan stride 0xd5: skip +6==0xffff, test
//   +0xa, cmp word [eax+0x1a],cx (fastcall param low word), test +0x1d,
//   store 0xffff at +6), tail 53/5b c3.  Inline-asm escape: FA carries a
//   dead xor edx,edx and the cx compare is the fastcall param's low half —
//   no source-level form makes CL keep either through /O2.  CL's auto
//   ebx spill reproduces FA's 53/5b prologue/epilogue.
//   Probe build/w4probe/b17_msgrs_v1.c — exact modulo fixup dwords.

extern char lastWeaponButton[];

void __fastcall MSGRemoveSecondaries(unsigned short id) {
    __asm {
        mov eax, offset lastWeaponButton + 0xf0
        xor edx, edx
    Lrep:
        cmp word ptr [eax + 6], 0xffff
        je Lcont
        mov bl, byte ptr [eax + 0xa]
        test bl, bl
        jne Lcont
        cmp word ptr [eax + 0x1a], cx
        jne Lcont
        mov bl, byte ptr [eax + 0x1d]
        test bl, bl
        je Lcont
        mov word ptr [eax + 6], 0xffff
    Lcont:
        add eax, 0xd5
        cmp eax, offset lastWeaponButton + 0x64c8
        jb Lrep
    }
}