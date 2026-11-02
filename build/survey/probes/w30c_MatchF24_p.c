/* 0x11730 _MatchF24@12 — v_p: array-param spelling */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(int pa[], int target, int delta)
{
    int cur, step;
    cur = pa[0];
    if (target == cur)
        return;
    if (delta == 0)
        return;
    step = ((int)_serviceTicks * delta) >> 8;
    if (target > cur) {
        cur += step;
        pa[0] = cur;
        if (target < cur)
            pa[0] = target;
    } else {
        cur -= step;
        pa[0] = cur;
        if (target > cur)
            pa[0] = target;
    }
}
