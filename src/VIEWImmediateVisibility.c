// _VIEWImmediateVisibility@0 @ rva 0xe0f0 — T_ImmediateVisibility(mainV)
//   then T_ImmediateVisibility(hud+0x78); the +0x78 addend bakes into the
//   push imm32 (probe d93 exact, pilotRanks precedent).
extern char mainV[];
extern char hud[];
extern void __stdcall T_ImmediateVisibility4(char *p);

void VIEWImmediateVisibility_q(void)
{
    T_ImmediateVisibility4(mainV);
    T_ImmediateVisibility4(hud + 0x78);
}
