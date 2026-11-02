// 0xd38a0 = 865152, unnamed gap, 15 B
// FA asm: push 1 / push 1 / push 0 / call $FA$_t_4d38b0 (CRT-style 3-arg exit
// wrapper) / add esp,0xc / ret.  No rel32 or abs32 refs anywhere in FA —
// unreferenced (likely CRT `abort`-family leftover: exit(0,1,1)).
extern void __cdecl CRTExit3(int code, int quick, int wide);
/* map _CRTExit3=$FA$_t_4d38b0 */

void __cdecl w25c_ExitTrap(void)
{
    CRTExit3(0, 1, 1);
}