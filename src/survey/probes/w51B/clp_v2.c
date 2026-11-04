/* wave 51B probe v1: CheckLandingParms rva 0x76010 (256 B)
 * clamp cascade: five test groups driving a shared 0/5/6 level via @Abs@4
 * fastcall and _curThingType word loads; thresholds 0x14/0x14/0x32/0xa/0x14 */
extern char curThing[];
extern char curThingType[];
int __fastcall Abs(int);

int w51B_clp_v1(void) {
    int p = 0;
    int v;
    v = Abs(*(int *)&curThing[0x18f] >> 8) - *(short *)&curThingType[0x14a];
    if (v > 0x14) p = 6;
    if (v > 0) { if (p < 5) p = 5; }
    v = Abs(*(int *)&curThing[0x193] >> 8) - *(short *)&curThingType[0x148];
    if (v > 0x14) { if (p < 6) p = 6; }
    if (v > 0) { if (p < 5) p = 5; }
    v = (*(int *)&curThing[0x34] >> 8) - *(short *)&curThingType[0x142];
    if (v > 0x32) { if (p < 6) p = 6; }
    if (v > 0) { if (p < 5) p = 5; }
    v = Abs(*(int *)&curThing[0x177] >> 8) - *(short *)&curThingType[0x144];
    if (v > 0xa) { if (p < 6) p = 6; }
    if (v > 0) { if (p < 5) p = 5; }
    v = -(*(short *)&curThingType[0x146] + *(short *)&curThing[0x22a]);
    if (v > 0x14) { if (p < 6) p = 6; }
    if (v > 0) { if (p < 5) p = 5; }
    return p;
}