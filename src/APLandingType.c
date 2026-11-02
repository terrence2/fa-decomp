// @APLandingType@8 @ rva 0xb6e60 (96 B) — FA asm: mov eax,[ecx+5] / test edx,edx
//   / mov eax,[eax+0xba] / jne / mov eax,-1 / ret / mov cl,[edx+0xe8] / test cl,cl
//   / je L1 / test al,0x40 / jne L1 / mov eax,-1 / ret / L1: test al,8 / je L2 /
//   mov eax,0x18 / ret / L2: mov cl,[edx+0xea] / test cl,cl / je L3 / test al,2 /
//   je L3 / mov eax,0x16 / ret / L3: test al,0x20 / je L4 / mov eax,0x18 / ret /
//   L4: cmp byte [edx+0xec],1 / sbb eax,eax / and eax,0xffffffe8 / add eax,0x17 /
//   ret. Fastcall (ecx=a, edx=b). Plain C: the flag word is read FIRST (both
//   dependent movs) with CL interleaving the independent test edx between them;
//   partial cl writes are unsigned char locals; the tail is the BriefMap
//   borrow-ternary family — (b+0xec byte) >= 1 ? 0x17 : -1 written so CL emits
//   cmp/sbb/and/add (unsigned-read >= 1 polarity). No external refs at all.
int __fastcall APLandingType_q(long a, long b)
{
    unsigned long fl = *(unsigned long *)(*(unsigned long *)(a + 5) + 0xba);
    unsigned char c1, c2;
    if (!b)
        return -1;
    c1 = *(unsigned char *)(b + 0xe8);
    if (c1 != 0 && !(fl & 0x40))
        return -1;
    if (fl & 8)
        return 0x18;
    c2 = *(unsigned char *)(b + 0xea);
    if (c2 != 0 && (fl & 2))
        return 0x16;
    if (fl & 0x20)
        return 0x18;
    return (*(unsigned char *)(b + 0xec) >= 1) ? 0x17 : -1;
}