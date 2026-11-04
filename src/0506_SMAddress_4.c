/* w38G _SMAddress@4 @ 0x696b0 (144 B, FPO ebp 4-reg) — v1.
 * FA: 4 pushes interleaved with the moffs avail test; binary search over
 * the 2-per-entry table (name ptr + id at +4), 2-byte-at-a-time walk, the
 * sbb/sbb -1 compare idiom; found returns entry id, else 0. */
extern long w38g_pu2b4;             /* -> _pilotsUpdated+0x2b4 */
extern long w38g_pu2bc;             /* -> _pilotsUpdated+0x2bc */
extern char *w38g_tabq[];           /* -> ?unAvailNames@@3PADA+0xc */

unsigned long __stdcall w38g_sma4(char *name)
{
    unsigned long ret;
    long avail;
    int lo, hi, mid, cmpv;
    char *s, *up;
    unsigned char b1, b2;

    avail = w38g_pu2b4;
    if (avail == 0)
        return 0;
    lo = 0;
    hi = (int)w38g_pu2bc - 1;
    ret = 0;
    while (hi >= lo) {
        mid = (lo + hi) >> 1;   /* signed sar form */
        up = w38g_tabq[mid];
        s = name;
        for (;;) {
            b1 = *(unsigned char *)s;
            b2 = *(unsigned char *)up;
            if (b1 != b2)
                break;
            if (b1 == 0) {
                cmpv = 0;
                goto done;
            }
            b1 = *(unsigned char *)(s + 1);
            b2 = *(unsigned char *)(up + 1);
            if (b1 != b2)
                break;
            s += 2;
            up += 2;
            if (b1 == 0) {
                cmpv = 0;
                goto done;
            }
        }
        cmpv = b1 < b2 ? -1 : 1;
done:
        ret = ((unsigned long *)w38g_tabq)[mid * 2 + 1];
        if (cmpv == 0)
            return ret;
        if (cmpv == -1)
            hi = mid - 1;
        else
            lo = mid + 1;
        if (hi < lo)
            ret = 0;
    }
    return ret;
}