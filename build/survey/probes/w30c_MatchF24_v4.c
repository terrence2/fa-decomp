/* 0x11730 _MatchF24@12 — v4: step split statements */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(int *p, int target, int delta)
{
    int cur, step;
    cur = (int)_serviceTicks * 0;
    step = 0;
    cur = *p;
    if (target == cur)
        return;
    if (delta == 0)
        return;
    step = (int)_serviceTicks;
    step = step * delta;
    step >>= 8;
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
