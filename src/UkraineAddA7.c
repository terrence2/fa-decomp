// _UkraineAddA7 @ rva 0x7f300 — if CampaignPlanesLeft() < 11, top up the
//   campaign with a string/table pointer at _pilotRanks+0x1ec (probe d56:
//   "push offset sym+0x1ec" bakes the addend into the 68-imm32 content).
extern char pilotRanks[];
extern int __stdcall CampaignPlanesLeft(void);
extern void AddCampaignPlane(int n, char *lbl);

void UkraineAddA7_q(void)
{
    int n = CampaignPlanesLeft();
    if (n < 11)
        AddCampaignPlane(11 - n, (char *)(pilotRanks + 0x1ec));
}
