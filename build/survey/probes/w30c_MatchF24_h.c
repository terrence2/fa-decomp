/* 0x11730 _MatchF24@12 — v_h: clamp spelled target<=cur / target>=cur with else-flip */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(int *p, int target, int delta)
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
        if (target < cur) {
            *p = target;
            return;
        }
        return;
    }
    cur -= step;
    *p = cur;
    if (target > cur) {
        *p = target;
        return;
    }
}
