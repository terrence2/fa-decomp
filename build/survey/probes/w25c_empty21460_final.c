// 0x21460 = 136288, unnamed gap, 16 B (1 code c3 + 15 census pad)
// FA asm: ret — empty body, one fastcall param in ecx (caller at 0x213cd in
// 0x21470: mov ecx,[0x524e58]; cmp/jne; e8 — no stack arg).
void __fastcall w25c_empty21460_q(int x)
{
}