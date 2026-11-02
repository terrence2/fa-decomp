/* v2: guard + separate do-while so pw init lands after the first test;
   x4 intermediate forces the two-step lea; no pre-increment copy. */
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
        pw = &w28a_wids[x4 * 4];
        do {
            w28a_wps(*pw, obj);
            pw++;
            i++;
        } while (w28a_wsizes[grp] > i);
    }
}
