/* 0x11730 _MatchF24@12 — v3: merged condition, cur from init decl */
extern short _serviceTicks;

void __stdcall w30c_MatchF24(int *p, int target, int delta)
{
    int cur = *p;
    int step;
    if (target != cur || delta == 0)
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
