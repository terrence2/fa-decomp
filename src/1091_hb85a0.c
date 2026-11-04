// 0xb85a0 (16 B) — mov ecx,0xe; jmp @EnterState@4; pad. Same recipe as entb.
extern void __fastcall EnterState_f(long n);   /* @EnterState@4 */
void __fastcall w27a_ente_q(void)
{
    EnterState_f(0xe);
}