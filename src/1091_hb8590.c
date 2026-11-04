// 0xb8590 (16 B) — mov ecx,0xb; jmp @EnterState@4; pad. Fastcall 1-reg
// tail-call wrapper, same recipe as w26a_b9660 (EXACT).
extern void __fastcall EnterState_f(long n);   /* @EnterState@4 */
void __fastcall w27a_entb_q(void)
{
    EnterState_f(0xb);
}