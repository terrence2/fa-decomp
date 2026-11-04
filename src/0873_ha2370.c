/* v2 — FA reads arg2 first (edx path: esi = tbl[*arg2]), compares
 * tbl[*arg2] (esi) vs tbl[*arg1] (eax), tie-breaks on *arg2 vs *arg1:
 *   -1 / 1 / -1 / setl.  CL canonicalizes cmp esi,eax -> cmp eax,esi
 * with inverted jcc (wave-19 a1-first wall) so that 4-B gets patched.
 */
extern void *w44B_tbl;   /* array-base pointer at ?rwrVol@@3GA+0x4 */

int __cdecl w44B_rankcmp(int *p1, int *p2)
{
    int rA = ((int *)*(void * volatile *)&w44B_tbl)[*p2];
    int rB = ((int *)*(void * volatile *)&w44B_tbl)[*p1];
    if (rA < rB)
        return -1;
    if (rA > rB)
        return 1;
    if (*p2 > *p1)
        return -1;
    return *p2 < *p1;
}