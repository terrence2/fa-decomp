// _FMResetTV@0 @ rva 0x79ed0 (30 B) — stdcall FMSetTV(0,0) then two dword
//   clears in reverse-address order: _curThing+0x2b3 first, +0x2af second
//   (probe d140).
extern void __stdcall FMSetTV(int a, int b);
extern char curThing[];
void __stdcall FMResetTV_q(void)
{
    FMSetTV(0, 0);
    *(long *)(curThing + 0x2b3) = 0;
    *(long *)(curThing + 0x2af) = 0;
}
