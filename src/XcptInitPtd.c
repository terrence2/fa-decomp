// __initptd @ rva 0xd9130 (19 B) — mov eax,[esp+4] / mov [eax+0x50],
//   __XcptActTab / mov dword [eax+0x14],1 / ret: CRT PTD initializer.
//   Probe d15_iptd byte-exact modulo the DIR32 target (0x51ab60).
extern int XcptActTab[];

void XcptInitPtd_q(void *p)
{
    *(long *)((char *)p + 0x50) = (long)XcptActTab;
    *(long *)((char *)p + 0x14) = 1;
}
