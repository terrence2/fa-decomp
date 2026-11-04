// ?GetJoystickType@@ v2 — the two caps checks merged as an || chain with a
// SHARED return-1 tail (FA shares the single b8 01 00 00 00 block behind
// both jae jumps; v1's separated ifs let CL go branchless sbb/inc).
extern char w43b_joyInit;   /* _w43b_joyInit=?joysticksInitialized@@3DA */
extern unsigned long w43b_joyDev;    /* _w43b_joyDev=?joystickDevices@@3KA */
extern unsigned long w43b_joyMask;   /* _w43b_joyMask=?joystickMask@@3KA */
extern char w43b_capB[];             /* _w43b_capB=?joystickCaps@@3PAUtagJOYCAPSA@@A */

long __cdecl w43b_gjt(unsigned long id)
{
    unsigned long ai;

    if (!w43b_joyInit)
        return 4;
    if (w43b_joyDev <= id)
        return 3;
    if (!(w43b_joyMask & (1 << id)))
        return 3;
    ai = id * 404;
    if (*(unsigned long *)&w43b_capB[ai + 0x68] >= 3 ||
        *(unsigned long *)&w43b_capB[ai + 0x3c] >= 4)
        return 1;
    return 0;
}