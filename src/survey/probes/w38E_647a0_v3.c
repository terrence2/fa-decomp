/* CTEval_waypointalt v3: WPPos fills pos[0..1] (FA: out-pos=&pos[0], e=pos[1]);
 * +0x11 field arg passed via its own extern (so CL pushes imm32). */
extern char __fastcall WPDoingWaypoints(void);
extern void __stdcall WPPos(long, long *);
extern long __stdcall T_Info(long, long, long, long, long, long);
extern long curThing15, curThingE8, curThing11;
extern long curThing;
extern unsigned short curId;

long __cdecl CTEval_waypointalt(void)
{
    unsigned long pos[3];
    long t, e;
    if (!WPDoingWaypoints()) {
        pos[1] = (unsigned long)curThing15;
    } else {
        WPPos((long)curThingE8, (long *)&pos[0]);
    }
    e = (long)pos[1];
    t = T_Info(curId, (long)&curThing, (long)&curThing11, 0, 0, 0);
    return (long)(e - t) >> 8;
}