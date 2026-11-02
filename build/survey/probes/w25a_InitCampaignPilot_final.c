void *memset(void *d, int v, unsigned int n);
char *strcpy(char *d, const char *s);
extern char campZone[];    /* _campaignPilot+0xdae */
extern unsigned short campFlag;   /* _campaignPilot+0xdac */
extern char campStr[];     /* _campaignPilot+0xd7f */
extern char campaignFile[];   /* identity */

void InitCampaignPilot_q(void)
{
    memset(campZone, 0, 0x1832);
    campFlag = 1;
    strcpy(campStr, campaignFile);
}
