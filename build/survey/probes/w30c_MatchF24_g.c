/* 0x11730 _MatchF24@12 — v_g: steps via extra var, cur recomputed from *p after checks */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(int *p, int target, int delta)
{
    int cur, step, sv;
    cur = *p;
    if (target == cur)
        return;
    if (delta == 0)
        return;
    sv = (int)_serviceTicks;
    step = sv * delta >> 8;
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
