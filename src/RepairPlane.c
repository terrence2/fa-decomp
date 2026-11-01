extern char pilotName[];
extern char hangarName[];
extern char campaignPilot[];
extern void __stdcall SelectRepairPlane(char *a, char *b, int c, int d);
void __RepairPlane(void)
{
    if (pilotName[0])
        SelectRepairPlane(campaignPilot, hangarName, 1, 1);
}
