/* variant 3: long rv local to force movsx eax,ax after the call */
extern short __stdcall DoDialogInfoBox(char *msg, int n);
extern void __stdcall LoadFile(char *a, int b, char *c, int d);
extern void __fastcall AbortCampaign_q(void);   /* -> ?AbortCampaign@@YIDXZ */
extern char strMenu[];        /* _pilotRanks+0x524 */
extern char strLoad[];        /* _pilotRanks+0x518 */
extern char campaignPilot[];  /* identity */
extern unsigned long campaignState;  /* identity */

void __fastcall CampaignMenu_q(unsigned char a)
{
    long rv;
    switch ((unsigned long)a) {
    case 1:
        rv = DoDialogInfoBox(strMenu, 3);
        if (rv != 1)
            return;
        LoadFile(strLoad, 0, campaignPilot, 0);
        campaignState = 4;
        break;
    case 2:
        AbortCampaign_q();
        break;
    }
}
