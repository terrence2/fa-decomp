// _CampaignPlanesLeft@0 @ rva 0x7f280 (29 B) — counted walk over 0xbc-byte
//   records from _campaignPilot+0xdbe to +0x1c6e: cmp word [ecx],0 / je +1
//   skips the single-byte inc eax / add ecx,0xbc / cmp,imm / jb loop
//   (probe d142; both record bounds are DIR32-with-addend imms).
extern char campaignPilot[];
int CampaignPlanesLeft_q(void)
{
    int n = 0;
    char *p = campaignPilot + 0xdbe;
    while (p < campaignPilot + 0x1c6e)
    {
        if (*(short *)p != 0)
            n++;
        p += 0xbc;
    }
    return n;
}
