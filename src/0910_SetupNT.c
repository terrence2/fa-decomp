// _SetupNT @ rva 0xa40a0 — t4a39b0(s, 0xa0) via fastcall (push 56 / call —
//   callee cleans 8), then SetupOT(s) (probe d90 exact).
extern void __fastcall t4a39b0(char *p, int n);
extern void SetupOT(char *s);

void SetupNT_q(char *s)
{
    t4a39b0(s, 0xa0);
    SetupOT(s);
}
