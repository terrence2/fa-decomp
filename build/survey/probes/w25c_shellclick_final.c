// 0x617b0 = 399280, unnamed gap, 16 B (11 code + 90 pad)
// FA asm: mov edx,1 / mov ecx,0x140 / jmp @ShellClickSound@8 — fastcall
// preload tail-jmp (15 refs from _INFO2Screen).  arg1 (ecx) = 0x140,
// arg2 (edx) = 1.
extern void __fastcall ShellClickSndQ(int a, int b);
/* map @ShellClickSndQ@8=@ShellClickSound@8 */

void __fastcall w25c_shellclick_q(void)
{
    ShellClickSndQ(0x140, 1);
}