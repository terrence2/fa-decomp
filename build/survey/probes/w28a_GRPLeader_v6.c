/* v6: v5 src at /O1 /Gy /G5: v3 at /O1: pid = &gids[x4*2] (correct grp*8 elements); v2 regs/shape otherwise. */
extern unsigned short w28a_gids[];       /* =_groupIds */
extern unsigned char w28a_gsizes[];      /* =_groupSizes */
extern char *w28a_ops[];                 /* =_objPtrs */

unsigned short __fastcall w28a_GRPLeader(short grp)
{
    unsigned long m;
    int i = 0;
    unsigned long x4;
    unsigned short *pid;
    int n;
    n = w28a_gsizes[grp];
    if (--n > 0) {
        x4 = grp * 4;
        m = 1;
        pid = &w28a_gids[x4 * 2];
        do {
            if (*(unsigned long *)(w28a_ops[*pid] + 1) & m) break;
            pid++;
            i++;
        } while (n > i);
    }
    return w28a_gids[grp * 10 + i];
}
