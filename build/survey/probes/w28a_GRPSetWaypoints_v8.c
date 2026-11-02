/* v8: decl (pb, i, x4) — pb declared first (FA's pw=ebx claim), bare truth entry. */
extern unsigned short w28a_gids[];      /* =_groupIds */
extern unsigned char w28a_gsizes[];     /* =_groupSizes */
extern void __stdcall w28a_wps(unsigned short id, void *obj);   /* =_WPSetWaypoints@8 */

void __stdcall w28a_GRPSetWaypoints(short grp, void *obj)
{
    unsigned short *pb;
    int i;
    unsigned long x4;
    if (w28a_gsizes[grp]) {
        x4 = grp * 4;
        pb = (unsigned short *)((char *)w28a_gids + x4 * 4);
        i = 0;
        do {
            w28a_wps(*pb, obj);
            pb++;
            i++;
        } while (w28a_gsizes[grp] > i);
    }
}
