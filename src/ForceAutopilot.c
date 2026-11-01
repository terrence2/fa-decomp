// @ForceAutopilot@4 @ rva 0x16200 — if autopilot flag 0x1000 not set,
//   set 0x2000; then SetAutopilot(1, a) (probe d97 exact).
extern char curThing[];
extern void __fastcall SetAutopilot(int on, int a);

void __fastcall ForceAutopilot_q(int a)
{
    unsigned long f = *(unsigned long *)((char *)curThing + 0x16f);
    if (!(f & 0x1000)) { *(unsigned long *)((char *)curThing + 0x16f) = f | 0x2000; }
    SetAutopilot(1, a);
}
