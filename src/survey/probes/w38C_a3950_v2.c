/* w38C 0xa3950 v2: signed dword compare on [1] field (FA jle), same reg
 * plan as v1 (eax walker, esi best, ebx/edx temps). */
extern char w38c_vdoA;  /* ?vdoColorProcess@@3FA + 0x10 */
extern char w38c_vdoB;  /* ?vdoColorProcess@@3FA + 0x8 */
extern char w38c_vdoC;  /* ?vdoColorProcess@@3FA + 0xa8 */
extern int _w38c_tt;    /* _timerTicks */

void __fastcall w38c_a3950(int val)
{
    signed int *cur = (signed int *)&w38c_vdoA;
    signed int *best = (signed int *)&w38c_vdoB;
    do {
        if (cur[1] < best[1])
            best = cur;
        cur += 2;
    } while (cur < (signed int *)&w38c_vdoC);
    best[0] = val;
    best[1] = _w38c_tt;
}