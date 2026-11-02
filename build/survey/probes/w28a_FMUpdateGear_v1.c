/* _FMUpdateGear@0 @ rva 0x50ba0 (96 B) — stdcall void(void):
   delta = _serviceTicks * 10922 / 256; gearAngle = TurnTowardAngle(
   gearAngle, (gearF & 0x40) ? 0 : 0x7fff, delta). */
extern short w28a_svc;                 /* =_serviceTicks (movsx read) */
extern unsigned long w28a_gearF;       /* =_curThing+0x16f */
extern unsigned short w28a_gearAng;    /* =_curThing+0x238 */
extern unsigned short __fastcall w28a_tta(unsigned short cur, unsigned short max, int delta);
    /* =@TurnTowardAngle@12 */

void __stdcall w28a_FMUpdateGear(void)
{
    int delta = w28a_svc * 10922 / 256;
    w28a_gearAng = w28a_tta(w28a_gearAng, (w28a_gearF & 0x40) ? 0 : 0x7fff, delta);
}
