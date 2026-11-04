/* _FPSUpdate@0 @ 0x84e60 (131 B code + 13 B tail pads).  Frame-rate sampler:
 * shifts the 10-entry _timeCompression tick ring up one slot, stores the
 * latest frame delta, and recomputes the FPS average.
 * void __stdcall FPSUpdate(void)   [no prologue, no pushes]
 *   ring = (ulong*)((char*)_timeCompression + 8);        0x549e50..0x549e74
 *   p = ring + 9;
 *   do { *p = *(p-1); p = p - 1; } while (p != ring);    [8b48fc 83e804 3d 90 894804 75ef]
 *   delta = _timerTicks - *(ulong*)((char*)_frameTicks+4);  [8b0d 3c9e5400; a1 809e5400; 2bc8]
 *   old = *(ulong*)((char*)_currentT+0x10);  now = _timerTicks;   [8b15 289e5400; a1]
 *   ring[0] = delta;                                     [890d 509e5400]
 *   lastT(0x549e80) = now;                               [a3 809e5400]
 *   if (old > now) return;                               [3bd0 7f40 — SIGNED jg]
 *   now = _timerTicks + 0x80;                            [a1; 05 80000000]
 *   *(ulong*)((char*)_currentT+0x10) = now;              [a3 289e5400]
 *   sum = 0;
 *   q = ring; while (q < (ulong*)_currentTicks) { sum += *q; q++; }   [b8 8b10 83c004 03ca 3d 72f2]
 *   if (sum == 0) { *(ulong*)((char*)_currentT+0x14) = 0; return; }   [85c9 750b c705... c3]
 *   *(ulong*)((char*)_currentT+0x14) = 0x3e800 / sum;    [b8 00e80300 99 f7f9 a3]
 * _timerTicks is re-read 3x (volatile in FA source); old/now/sum/fps signed
 * longs (jg 0x7f and cltd/idiv); ring-end compares unsigned (jb 0x72 tail).
 */
extern volatile unsigned long _timerTicks;    /* 0x549e3c */
extern unsigned char _timeCompression[];      /* 0x549e48 */
extern unsigned char _currentT[];             /* 0x549e18 */
extern unsigned char _frameTicks[];           /* 0x549e7c */
extern unsigned char _currentTicks[];         /* 0x549e78 */

void __stdcall FPSUpdate(void)
{
    unsigned long *p, *q;
    long delta, old, now, sum;

    p = (unsigned long *)((char *)_timeCompression + 0x2c);
    do {
        *p = *(p - 1);
        p = p - 1;
    } while (p != (unsigned long *)((char *)_timeCompression + 8));
    delta = _timerTicks - *(unsigned long *)((char *)_frameTicks + 4);
    old = *(long *)((char *)_currentT + 0x10);
    now = _timerTicks;
    *(unsigned long *)((char *)_timeCompression + 8) = delta;
    *(unsigned long *)((char *)_frameTicks + 4) = now;
    if (old > now)
        return;
    now = _timerTicks + 0x80;
    *(long *)((char *)_currentT + 0x10) = now;
    sum = 0;
    q = (unsigned long *)((char *)_timeCompression + 8);
    while (q < (unsigned long *)_currentTicks) {
        sum += *q;
        q = q + 1;
    }
    if (sum == 0) {
        *(unsigned long *)((char *)_currentT + 0x14) = 0;
        return;
    }
    *(unsigned long *)((char *)_currentT + 0x14) = 0x3e800 / sum;
}