/* v2 C route: CL will drop the useless push ebx/pop ebx (5-B diff) unless a
 * dummy ebx user exists; probe anyway to see scheduler/encodings. */
extern char campaignPilot[];
extern long campaignFailures;
extern short (__cdecl *w35h_cfp)(long);

long __stdcall CallCampaignFailureC(long p)
{
    campaignFailures = *(long *)(campaignPilot + 0x1f88);
    return (long)(*w35h_cfp)(p);
}