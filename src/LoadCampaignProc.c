// _LoadCampaignProc @ rva 0x7f130 (18 B) — stdcall RMAccess(_campaignFile, 0)
//   result stored into the ?campaignProc@@3P6AFJ@ZA function pointer (a3);
//   push 0 goes before the campaignFile offset (right-to-left, probe d141).
extern char campaignFile[];
extern void (__stdcall *campProc)(int);
extern int __stdcall RMAccess(char *a, int b);
void LoadCampaignProc_q(void)
{
    campProc = (void (__stdcall *)(int))RMAccess(campaignFile, 0);
}
