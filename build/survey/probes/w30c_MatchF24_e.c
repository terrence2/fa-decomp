/* 0x11730 _MatchF24@12 — v_e: long types */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(long *p, long target, long delta)
{
    long cur, step;
    cur = *p;
    if (target == cur)
        return;
    if (delta == 0)
        return;
    step = ((long)_serviceTicks * delta) >> 8;
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
