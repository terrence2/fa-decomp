// __ArmPlane@4 — polarity flip: FA tests doArmPlane, jne +0x12 SKIPS the
// early-return path which sits first; int r so movsx lands right after call.
extern unsigned char w27a_dab;      /* _doArmPlane */
extern unsigned char w27a_pnB;      /* _pilotName */
extern void *w27a_cpP;              /* _campaignPilot */
extern short __fastcall ArmPlane_f(void *cp);    /* @ArmPlane@4 */
int __stdcall w27a_arm_q(unsigned char *p)
{
    int r;
    if (w27a_dab == 0)
    {
        r = (*p < 1 ? 13 : 18);
        return r;
    }
    r = ArmPlane_f(w27a_pnB != 0 ? &w27a_cpP : (void *)0);
    *p = (unsigned char)(r == 0x12);
    return r;
}
