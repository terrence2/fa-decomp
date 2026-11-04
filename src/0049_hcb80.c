/* unnamed 0xcb80: 16-bit menu walk. fastcall ecx param; si counter,
   dx=(x>>8) top-level walk, cx&0xff item walk. firstMenu: list of MENU
   (next at +0, child list at +4); each child item: sub at +4, list next at +0. */
extern void *firstMenu;   /* map: ?firstMenu@@3PAUMENU@@A */

void * __fastcall w44acMenuWalk(unsigned short x)
{
    void *m = firstMenu;
    unsigned short i = 1;
    unsigned short hi, lo;
    void *c, *e1, *e2;

    if (m) {
        hi = (unsigned short)(x >> 8);
        while (i < hi) {
            i++;
            m = *(void **)m;
            if (m == 0)
                break;
        }
        if (m) {
            i = 1;
            c = *(void **)((char *)m + 4);
            if (c) {
                lo = (unsigned short)(x & 0xff);
                for (;;) {
                    if (i >= lo)
                        return c;
                    i++;
                    e1 = *(void **)((char *)c + 4);
                    if (e1 == 0)
                        goto adv;
                    e2 = *(void **)((char *)e1 + 4);
                    if (e2 == 0)
                        goto adv;
                    for (;;) {
                        if (i >= lo)
                            return e2;
                        i++;
                        e2 = *(void **)e2;
                        if (e2 == 0)
                            break;
                    }
adv:
                    c = *(void **)c;
                    if (c == 0)
                        return 0;
                }
            }
        }
    }
    return 0;
}