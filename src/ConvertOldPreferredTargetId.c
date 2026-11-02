// ?ConvertOldPreferredTargetId@@YIJG@Z @ rva 0x800f0 (39 B code + 10 B
// 8d49/8da424 pad) — fastcall unsigned short id in cx: mov ax,cx keeps the
// word copy form; masks 0x1fff / 0x1fffffff via and eax,imm; the two
// byte-aligned tests fold to test ah/test ch (f6 c4 10, f6 c5 20/40/80);
// or eax,imm32 for the three high-bit sign-upgrades and one sign extension.
// MASM gives every A-form (66 8b c1, 25, 0d, f6 c5) natively.
__declspec(naked) long __fastcall ConvertOldPreferredTargetId_q(unsigned short id)
{
    __asm {
        mov  ax, cx
        and  eax, 1fffh
        test ah, 10h
        je   L1
        or   eax, 0ffffe000h
    L1: and  eax, 1fffffffh
        test ch, 20h
        je   L2
        or   eax, 20000000h
    L2: test ch, 40h
        je   L3
        or   eax, 40000000h
    L3: test ch, 80h
        je   L4
        or   eax, 80000000h
    L4: ret
    }
}