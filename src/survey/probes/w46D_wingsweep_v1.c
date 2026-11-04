/* w46D FMUpdateWingSweep rva 330752 (0x450c00) v1 */
extern long __stdcall COMinSpeed_q(void);      /* map: _COMinSpeed_q@0=_COMinSpeed@0 */
extern long __stdcall COMaxSpeed_q(void);      /* map: _COMaxSpeed_q@0=_COMaxSpeed@0 */
extern long w46d_ct34;                         /* map: _w46d_ct34=_curThing+0x34 */
extern unsigned short w46d_ct1a1;              /* map: _w46d_ct1a1=_curThing+0x1a1 */

void __stdcall w46d_wsweep_q(void)             /* map: _w46d_wsweep_q@0=_FMUpdateWingSweep@0 */
{
    long lo, hi, q, m, cur, r;
    cur = w46d_ct34;
    lo = COMinSpeed_q() << 8;
    hi = (COMaxSpeed_q() << 8) - lo;
    q = lo + hi / 4;
    m = lo + hi / 2;
    if (q > cur) {
        w46d_ct1a1 = 0;
        return;
    }
    if (cur >= m) {
        w46d_ct1a1 = 0x7fff;
        return;
    }
    r = 0x7fff * (cur - q) / (m - q);
    w46d_ct1a1 = (unsigned short)r;
}