/* ?AbortCampaign@@YIDXZ @ 0x7f8e0 (48B)
   FA: a0 playerState; je; push 3/strAbort; call _DoDialogInfoBox@8;
   cmp ax,1; je; xor al,al; ret; CampaignOff(); mov [campaignState],0x11;
   mov al,1; ret. NO pad (chunk is 48B, code ends flush at 0x2f). */
extern unsigned char playerStateQ;    /* -> ?stats_playerState@@3JA+0x4 */
extern short __stdcall DoDialogInfoBox(char *msg, int n);
extern char strAbort[];               /* -> _pilotRanks+0x4c0 */
extern void __fastcall CampaignOff(void);
extern unsigned long campaignState;   /* identity */

char __fastcall AbortCampaign_q(void)
{
    if (playerStateQ)
        if (DoDialogInfoBox(strAbort, 3) != 1)
            return 0;
    CampaignOff();
    campaignState = 0x11;
    return 1;
}
