// _FMUpdateBay@0 @ rva 0x51d30 (80 B) — probe v2 (no s local).
extern char curThingQ[];   /* _curThing */
extern short serviceTicks; /* _serviceTicks */
extern unsigned short __fastcall TurnTowardAngle_q(unsigned short h, unsigned short d, unsigned long a3); /* @TurnTowardAngle@12 */

void __stdcall FMUpdateBay_q(void)
{
    *(unsigned short *)&curThingQ[0x23a] = TurnTowardAngle_q(
        *(unsigned short *)&curThingQ[0x23a],
        (unsigned short)((*(unsigned long *)&curThingQ[0x16f] & 0x200) ? 0 : 0x7fff),
        (unsigned long)(serviceTicks * 16383 / 256));
}
