/* v3: x4 = grp*4 dword step; pw = &wids[x4*2] (byte 4*x4 = grp*16) —
   lea [esi*4]+0 then lea [eax*4+wids]. */
extern unsigned short w28a_wids[];     /* =_wingIds */
extern unsigned char w28a_wsizes[];    /* =_wingSizes */
extern void __stdcall w28a_wps(unsigned short id, void *obj);  /* =_WPSetWaypoints@8 */

void __stdcall w28a_WNGSetWaypoints(short grp, void *obj)
{
    unsigned long x4;
    unsigned short *pw;
    int i = 0;
    if (w28a_wsizes[grp] > i) {
        x4 = grp * 4;
        pw = &w28a_wids[x4 * 2];
        do {
            w28a_wps(*pw, obj);
            pw++;
            i++;
        } while (w28a_wsizes[grp] > i);
    }
}
