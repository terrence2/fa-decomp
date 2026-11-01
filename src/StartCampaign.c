// __StartCampaign@0 @ rva 0x7eaf0 — call _CampaignSelect@0 / cmp ax,0xffff /
//   jne next / xor eax,eax / ret / xor ecx,ecx / call @PilotScreen@4 / cmp
//   ax,1 / sbb eax,eax / inc eax / ret (probe w8_sc: unsigned-short r, both
//   tail forms exact; signed short r gives test/setg instead). CampaignSel's
//   tail-jne skips into the second section, matching this two-block single
//   exit structure.
extern short __cdecl CampaignSelect(void);
extern unsigned short __fastcall PilotScreen_x(int a);

int StartCampaign(void)
{
    unsigned short r = CampaignSelect();
    if (r == 0xffff)
        return 0;
    r = PilotScreen_x(0);
    return r >= 1;
}
