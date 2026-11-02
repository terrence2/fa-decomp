/* 0x11730 _MatchF24@12 — v_j: returns the clamped cur (FA leaves it in eax) */
extern short _serviceTicks;

long __stdcall w30c_MatchF24(int *p, int target, int delta)
{
    int cur, step;
    cur = *p;
    if (target == cur)
        return (long)cur;
    if (delta == 0)
        return (long)cur;
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
    return (long)cur;
}
