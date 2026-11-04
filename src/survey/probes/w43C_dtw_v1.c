/* _CTEval_disttowaypoint (112 B) - cdecl void(void): if
   WPDoingWaypoints(): WPPos(*(long *)(curThing+0xe8), pt) else fill
   pt[0..2] (pt[2] from materialized base (long*)(curThing+0x11) + 8);
   pt[1] reloaded from curThing+0x15 after the split; return
   Dist((long)(curThing+0x11), pt) >> 8 (sar eax,8). */
extern char curThing[];                          /* _curThing */
extern char __fastcall WPDoingWaypoints(void);   /* @WPDoingWaypoints@0 */
extern void __stdcall WPPos(long n, long *pt);   /* _WPPos@8 */
extern long __stdcall Dist(long a, long *pt);    /* _Dist@8 */
long __cdecl w43c_dtwq(void)
{
    long pt[3];
    if (WPDoingWaypoints())
        WPPos(*(long *)(curThing + 0xe8), pt);
    else {
        long *bp = (long *)(curThing + 0x11);
        pt[0] = bp[0];
        pt[1] = *(long *)(curThing + 0x15);
        pt[2] = bp[2];
    }
    pt[1] = *(long *)(curThing + 0x15);
    return Dist((long)(curThing + 0x11), pt) >> 8;
}
