/* _GRPSetWaypoints@8 @ rva 0x5ebb0 (80 B) — stdcall void(short grp, void *obj):
   pb = &groupIds[grp*8]; i = 0; for (i = 0; i < groupSizes[grp]; i++)
   WPSetWaypoints(*pb++, obj). */
extern unsigned short w28a_gids[];      /* =_groupIds */
extern unsigned char w28a_gsizes[];     /* =_groupSizes */
extern void __stdcall w28a_wps(unsigned short id, void *obj);   /* =_WPSetWaypoints@8 */

void __stdcall w28a_GRPSetWaypoints(short grp, void *obj)
{
    unsigned short *pb;
    int i;
    for (i = 0, pb = &w28a_gids[grp * 8]; i < w28a_gsizes[grp]; i++)
        w28a_wps(*pb++, obj);
}
