// _RestoreAutopilot@0 @ rva 0x16220 — if flag 0x2000 set, clear it, store,
//   SetAutopilot(0, 0) (probe d98 exact).
extern char curThing[];
extern void __fastcall SetAutopilot(int on, int a);

void RestoreAutopilot_q(void)
{
    unsigned long f = *(unsigned long *)((char *)curThing + 0x16f);
    if (f & 0x2000) {
        f &= ~0x2000;
        *(unsigned long *)((char *)curThing + 0x16f) = f;
        SetAutopilot(0, 0);
    }
}
