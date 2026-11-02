// 0x7ec30 __SelectPlane@4 (80 B) — v1
// If the screens/selector flags are off, borrow-ternary tail on *p
// (BriefMap d64 family: cmp [eax],1 / sbb / and -2 / +0xe). Otherwise
// SelectRepairPlane(arg1=pilot ? campaignPilot : 0, hangarName, 0, 1),
// FA dedups the (1,0,name) pushes before the pilotName test and
// duplicates call+ret4 per arm.
extern char w29a_doScreens, w29a_doSelectPlane;
extern char w29a_pilotName[];      /* _pilotName */
extern char w29a_hangar[];         /* ?hangarName@@3PADA */
extern char w29a_campaignPilot[];  /* _campaignPilot */
extern long __stdcall w29a_SRP(unsigned long a, char *b, unsigned long c, unsigned long d);
                                   /* _SelectRepairPlane@16 */

long __stdcall w29a_SelectPlane(char *p)
{
    if (!w29a_doScreens || !w29a_doSelectPlane)
        return (*(unsigned char *)p >= 1) ? 14 : 12;
    if (w29a_pilotName[0] != 0)
        return w29a_SRP((unsigned long)w29a_campaignPilot, w29a_hangar, 0, 1);
    else
        return w29a_SRP(0, w29a_hangar, 0, 1);
}