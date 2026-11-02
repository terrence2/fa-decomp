// @GetTargetPositions@4 @ rva 0x13f10 (80 B) — probe v3 (pd local, deferred).
extern int numVisibleTargets;            /* _numVisibleTargets */
extern unsigned short visibleTargetIds[];/* _visibleTargetIds */
extern void *objPtrs[];                  /* _objPtrs */
extern int __stdcall GRTo2d(int val, unsigned short *pos); /* _GRTo2d@8 */

void __fastcall GetTargetPositions_q(unsigned short *pos)
{
    int i = 0;
    unsigned short *pw, *pd;
    if (numVisibleTargets > 0) {
        pw = visibleTargetIds;
        pd = pos;
        do {
            if (GRTo2d((int)objPtrs[*pw] + 0x11, pd) < 0)
                *pd = 0x8000;
            pw++;
            pd += 2;
            i++;
        } while (numVisibleTargets > i);
    }
}