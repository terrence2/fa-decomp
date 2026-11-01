// __ContinueCampaign@0 @ rva 0x7eb10 — mov ecx,1 / call @PilotScreen@4 /
//   cmp ax,1 / sbb eax,eax / inc eax / ret (probe w2_cont exact).
extern unsigned short __fastcall PilotScreen_x(int a);

int ContinueCampaign(void)
{
    unsigned short r = PilotScreen_x(1);
    return r >= 1;
}
