/* w37B 0x76fa0 (rva 487328, 128 B) _COTurnRate@0 v2. v1's only real diffs
 * were the curThing+0x34 staging: FA stages it in ESI (push esi / mov
 * esi,[ct34] before the COBrv call / sar esi,8 after / mov edx,esi), so the
 * C must hold it in a live-across-call local. Each of the 6 epilogues ends
 * pop esi / ret. */
extern char curThing;                  /* _curThing (identity) */
extern long w37b_ct34X;                /* _curThing+0x34 */
extern short w37b_ttA5X;               /* _curThingType+0x105 */
extern short w37b_ttA7X;               /* _curThingType+0x107 */
extern short w37b_tt5dX;               /* _curThingType+0x5d */
extern void *__stdcall COBrv(void);            /* _COBrv@0 */
extern long __fastcall GToTurn(long a, long shift);      /* @GToTurn@8 */
extern long __fastcall F24ToPA(long v);                 /* @F24ToPA@4 */
extern short __stdcall PROJEngineState(void);   /* _PROJEngineState@0 */

int __stdcall COTurnRate(void)
{
    long sh;
    long t;

    if (curThing == 4) {
        sh = w37b_ct34X;
        t = *(short *)((char *)COBrv() + 10);
        return F24ToPA(GToTurn(t, sh >> 8)) & 0xffff;
    }
    if (curThing == 6) {
        switch (PROJEngineState()) {
        case 0:
            return 0;
        case 1:
            return w37b_ttA5X;
        case 2:
            return w37b_ttA7X;
        }
        return 0;
    }
    return w37b_tt5dX;
}