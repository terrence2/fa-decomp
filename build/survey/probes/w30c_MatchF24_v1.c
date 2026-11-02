/* 0x11730 _MatchF24@12 — v1
   fixed-point match-toward-target helper; step = (short)_serviceTicks * delta >> 8 */
extern short _serviceTicks;

void __fastcall w30c_MatchF24(int *p, int target, int delta)
{
    int cur, step;
    cur = *p;
    if (target == cur)
        return;
    if (delta == 0)
        return;
    step = ((int)_serviceTicks * delta) >> 8;
    if (target > cur) {
        cur += step;
        *p = cur;
        if (target < cur)
            *p = target;
    } else {
        cur -= step;
        *p = cur;
        if (target > cur)
            *p = target;
    }
}