// _CampaignSave @ rva 0x7f840 = 522304, 80 B (byte _pilotsUpdated=1; push
//   esi/edi; RMAccess(pilotName,0x10c) stdcall; if (eax) inline rep movs:
//   esi=campaignPilot, edi=result, ecx=0x978; SaveFile(pilotName,
//   campaignPilot,0x25e0) cdecl; if (!al) CampaignDiskError call + pop
//   epilogue (no tail-jmp: esi/edi saved). v2: memcpy INTRINSIC + uchar
//   SaveFile return so the test uses al).
extern unsigned char w26_pilotsUpdated; /* map _w26_pilotsUpdated=_pilotsUpdated */
extern unsigned char w26_pilotName[]; /* map _w26_pilotName=_pilotName */
extern unsigned char w26_campaignPilot[]; /* map _w26_campaignPilot=_campaignPilot */
extern unsigned long __stdcall RMAccessQ(void *name, unsigned int size); /* map _RMAccessQ@8=_RMAccess@8 */
extern unsigned char __cdecl SaveFileQ(void *name, void *data, unsigned int size); /* map _SaveFileQ=_SaveFile */
extern void __cdecl CampaignDiskErrorQ(void); /* map _CampaignDiskErrorQ=?CampaignDiskError@@YAXXZ */
extern void *__cdecl memcpy(void *d, const void *s, unsigned int n); /* intrinsic - no map */

void w26c_CampaignSave_q(void)
{
    unsigned char *d;
    w26_pilotsUpdated = 1;
    d = (unsigned char *)RMAccessQ((void *)w26_pilotName, 0x10c);
    if (d)
        memcpy(d, (void *)w26_campaignPilot, 0x25e0);
    if (!SaveFileQ((void *)w26_pilotName, (void *)w26_campaignPilot, 0x25e0))
        CampaignDiskErrorQ();
}