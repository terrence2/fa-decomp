/* _MISSIONCheckSuccess@0 @ rva 0x849b0 (80 B) — stdcall void(void):
   if (thisComputer) return;
   if (campaignFailed+4 > currentTime [ushort unsigned cmp]) return;
   campaignFailed+4 = currentTime + 4;
   old = missionSucceeded; if ((missionSucceeded =
   CallMissionProc(missionName, 1)) != old) MPSendMissionSucceeded(); */
extern long w29e_tc;           /* =_thisComputer */
extern unsigned short w29e_ct; /* =_currentTime */
extern unsigned short w29e_cf4;/* =_campaignFailed+0x4 */
extern unsigned long w29e_ms;  /* =_missionSucceeded */
extern char w29e_mn[];         /* =_missionName */
extern unsigned long __stdcall w29e_cmi(char *n, long a); /* =_CallMissionProc@8 */
extern void __stdcall w29e_sms(void);   /* =?MPSendMissionSucceeded@@YGXXZ */

void __stdcall MISSIONCheckSuccessW(void)
{
    unsigned short t;
    unsigned long oldS;
    if (w29e_tc != 0)
        return;
    t = w29e_ct;
    if (w29e_cf4 > t)
        return;
    w29e_cf4 = t + 4;
    oldS = w29e_ms;
    if (oldS != (w29e_ms = w29e_cmi(w29e_mn, 1)))
        w29e_sms();
}