// 0x1f2d0 = 128464, unnamed gap, 16 B (14 code, no census tail)
// FA asm (fastcall 1 param in ecx — callers mov cl,[..]/e8; 3 refs in the
// next-door 0x1f2e0 chunk): cmp cl,0xd / je ret1 / cmp cl,0xa / je ret1 /
// xor al,al / ret / ret1: mov al,1 / ret.
char __fastcall w25c_IsCrNl_q(unsigned char c)
{
    if (c == 0x0d || c == 0x0a)
        return (char)1;
    return (char)0;
}