/* @GRPLeader@4 @ rva 0x5e990 (96 B) — fastcall ushort(short grp):
   n = groupSizes[grp]; if (--n > 0) scan groupIds[grp*8 + i] (mask=1)
   until objPtrs[id]+1 & 1; return groupIds[grp*10 + i]. */
extern unsigned short w28a_gids[];       /* =_groupIds */
extern unsigned char w28a_gsizes[];      /* =_groupSizes */
extern char *w28a_ops[];                 /* =_objPtrs */

unsigned short __fastcall w28a_GRPLeader(short grp)
{
    unsigned long m = 1;
    unsigned short *pid = &w28a_gids[grp * 8];
    int i = 0;
    int n = w28a_gsizes[grp];
    if (--n > 0) {
        do {
            if (*(unsigned long *)(w28a_ops[*pid] + 1) & m) break;
            pid++;
            i++;
        } while (i < n);
    }
    return w28a_gids[grp * 10 + i];
}
