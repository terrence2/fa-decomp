// 0x23dd0 = 146912, unnamed gap, 16 B (3 code 32 c0 c3 + 13 pad)
// FA asm: xor al,al / ret — char-return-0 fastcall (all 3 callers load ecx
// then call: 0x2365c, 0x281df = mov ecx,[0x531d60]; e8, 0x2ada4 same shape).
char __fastcall w25c_alret0_q(int x)
{
    return (char)0;
}