// w26a_b9660 @ rva 0xb9660 (761952, unnamed 16 B orphan) — FA bytes (raw):
//   b9 19 00 00 00       mov ecx, 0x19
//   e9 56 9e fa ff       jmp @EnterState@4   (rel32, ext tail-jmp)
//   8d 9b 00 00 00 00    (6 B census pad)
// Fastcall 1-reg tail-call wrapper: EnterState(0x19), this-arg discarded.
extern void __fastcall EnterState_f(long n);   /* @EnterState@4 */
void __fastcall w26a_b9660(void)
{
    EnterState_f(0x19);
}