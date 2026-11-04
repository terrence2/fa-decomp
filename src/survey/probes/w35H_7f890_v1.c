/* _CampaignOff @ rva 0x7f890 (80 B, 1 B pad) -- cdecl void(void).
 * RMFree(&campaignFile); campaignProc=0; word 0: pilot[0xdae]/[0xdac];
 * byte 0: pilot[0xd7f], pilot[0xd8c], campaignFile, pilotName,
 * campaignName; campaignPlane=-1 (c7 05); missionName byte 0.
 * w30g trick: stage the zero in locals so CL emits reg (88/66 89) stores
 * instead of c6/c7 imm forms. */
extern void __stdcall RMFree(unsigned long);
extern char campaignPilot[];
extern char campaignFile;
extern char pilotName;
extern char campaignName;
extern char missionName;
extern unsigned long campaignPlane;
extern short (__cdecl *w35h_cfp)(long);

void CampaignOff(void)
{
    unsigned short wz;
    unsigned char cz;

    RMFree((unsigned long)&campaignFile);
    wz = 0;
    cz = 0;
    *(unsigned short *)(campaignPilot + 0xdae) = wz;
    w35h_cfp = 0;
    *(unsigned short *)(campaignPilot + 0xdac) = wz;
    campaignPilot[0xd7f] = cz;
    campaignPilot[0xd8c] = cz;
    campaignFile = cz;
    pilotName = cz;
    campaignName = cz;
    campaignPlane = 0xffffffff;
    missionName = cz;
}