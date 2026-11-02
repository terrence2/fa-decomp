/* @CampaignMenu@4 @ 0x7f910 (80B)
   FA switch layout: widen (xor eax,eax; mov al,cl); cmp eax,1/je arm1;
   cmp eax,2/je arm2; ret(default); arm1 = DoDialogInfoBox (movsx eax,ax;
   cmp eax,1; jne ret) then LoadFile(strLoad?,...) — pushes RTL:
   0(arg4), campaignPilot(arg3), 0(arg2), strLoad(arg1); campaignState=4; ret.
   arm2 = tail-jmp ?AbortCampaign@@YIDXZ. */
extern short __stdcall DoDialogInfoBox(char *msg, int n);
extern void __stdcall LoadFile(char *a, int b, char *c, int d);
extern void __fastcall AbortCampaign_q(void);   /* -> ?AbortCampaign@@YIDXZ */
extern char strMenu[];        /* _pilotRanks+0x524 */
extern char strLoad[];        /* _pilotRanks+0x518 */
extern char campaignPilot[];  /* identity */
extern unsigned long campaignState;  /* identity */

void __fastcall CampaignMenu_q(unsigned char a)
{
    switch ((unsigned long)a) {
    case 1:
        if ((long)DoDialogInfoBox(strMenu, 3) != 1)
            return;
        LoadFile(strLoad, 0, campaignPilot, 0);
        campaignState = 4;
        break;
    case 2:
        AbortCampaign_q();
        break;
    }
}
