/* v3: byte-pointer lea step (char*) + x4 dword step. */
extern unsigned short w28a_gids[];      /* =_groupIds */
extern unsigned char w28a_gsizes[];     /* =_groupSizes */
extern void __stdcall w28a_wps(unsigned short id, void *obj);   /* =_WPSetWaypoints@8 */

void __stdcall w28a_GRPSetWaypoints(short grp, void *obj)
{
    unsigned long x4;
    unsigned short *pb;
    int i = 0;
    if (w28a_gsizes[grp] != 0) {
        x4 = grp * 4;
        pb = (unsigned short *)((char *)w28a_gids + x4 * 4);
        do {
            w28a_wps(*pb, obj);
            pb++;
            i++;
        } while (w28a_gsizes[grp] > i);
    }
}
