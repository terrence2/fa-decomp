/* _COGPullDrag@0 @ 0x77370 — v3: accumulate form q=cw[0]; q+=cw[1]; */
extern short w28b_cw[2];       /* -> _curThing+0x25d */
extern short w28b_t1;          /* -> _curThingType+0x17b */
extern short w28b_t2;          /* -> _curThingType+0x16b */
extern char w28b_fl;           /* -> _curThing+0x10 */
extern short w28b_dm;          /* -> _dam+0x7d */

char __stdcall w28b_cog_f(void)
{
    int q, r;
    q = w28b_cw[0];
    q += w28b_cw[1];
    q = q * w28b_t1 / 100;
    r = q + 100;
    if (w28b_fl & 0x80)
        r += w28b_dm;
    return (char)(w28b_t2 * r / 100);
}
