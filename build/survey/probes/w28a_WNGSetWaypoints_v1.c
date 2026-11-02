/* _WNGSetWaypoints@8 @ rva 0x5de80 (80 B) — stdcall void(short grp, void *obj):
   pw = &wingIds[grp*8]; i = 0; while (wingSizes[grp] > i) {
   WPSetWaypoints(*pw++, obj); i++; } */
extern unsigned short w28a_wids[];     /* =_wingIds */
extern unsigned char w28a_wsizes[];    /* =_wingSizes */
extern void __stdcall w28a_wps(unsigned short id, void *obj);  /* =_WPSetWaypoints@8 */

void __stdcall w28a_WNGSetWaypoints(short grp, void *obj)
{
    unsigned short *pw = &w28a_wids[grp * 8];
    int i = 0;
    while (w28a_wsizes[grp] > i) {
        w28a_wps(*pw++, obj);
        i++;
    }
}
