/* v2: x4/m/pid init inside the --n guard; decl order m,i,x4,pid,n;
   bottom condition n > i (FA cmp i,n;jl). */
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
        pid = &w28a_gids[x4 * 4];
        do {
            if (*(unsigned long *)(w28a_ops[*pid] + 1) & m) break;
            pid++;
            i++;
        } while (n > i);
    }
    return w28a_gids[grp * 10 + i];
}
