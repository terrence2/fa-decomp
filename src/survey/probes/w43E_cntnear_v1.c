/* FA 0x4141a0 @ContactNearestTo@8?? @12 — fastcall(c, x, y), ushort result */
extern long numContacts;                    /* ?numContacts@@3JA */
extern short grModeW[];                     /* _grMode+0x6 (divisor word) */
extern unsigned short __stdcall CPGetContact(long idx); /* ?CPGetContact@@YGGJ@Z */

unsigned short __fastcall w43E_ContactNearestTo(long listp, long x, long y)
{
    unsigned short r, res;
    long i, best, bestD, e;

    i = 0;
    best = -1;
    bestD = 0x7fffffff;
    res = 0;
    while (i < (long)numContacts) {
        r = CPGetContact(i);
        if (r) {
            long dx = *(short *)listp - x;
            e = (dx < 0 ? -dx : dx) << 8;
            e /= (long)*(short *)grModeW;
            {
                long dy = *(short *)((char *)listp + 2) - y;
                e += (dy < 0 ? -dy : dy);
            }
            if (bestD > e || best == -1) {
                best = i;
                bestD = e;
            }
        }
        listp += 4;
        i++;
    }
    if (best == -1)
        return 0;
    return CPGetContact(best);
}