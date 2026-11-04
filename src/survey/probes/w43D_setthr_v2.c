/* 0x9dcf0 @PLANESetThrottle@8 0x70 — long w in EAX, volatile reloads, goto-shared end */
extern volatile unsigned short w43D_th;   /* _curThing+0x1f2 */
extern unsigned long w43D_th32;           /* _curThing+0x1ee */
extern volatile unsigned long w43D_ct16f; /* _curThing+0x16f */
extern unsigned long w43D_tt153;          /* _curThingType+0x153 */
extern unsigned short curId;
extern unsigned short playerId;
extern unsigned long throttle;

void __fastcall PLANESetThrottle(long thr, char flag)
{
    long w;
    w = thr;
    if (w < 0x64)
        goto have;
    w = 0x64;
have:
    w43D_th = (unsigned short)w;
    if ((unsigned short)curId == w43D_th)
        throttle = (long)(short)w43D_th;
    if (flag)
        w43D_th32 = (long)(short)w43D_th << 8;
    if (thr <= 0x64)
        goto L_end;
    if (w43D_tt153 == 0)
        goto L_end;
    w43D_ct16f = w43D_ct16f | 0x20u;
    return;
L_end:
    w43D_ct16f = w43D_ct16f & ~0x20u;
}
