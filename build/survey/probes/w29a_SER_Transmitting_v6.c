// 0x4b4e0 — v6: unsigned char eq; r = (eq == 0)
struct W29OQ { long head; long tail; };
extern struct W29OQ w29a_oq;
extern char __cdecl w29a_fgCheck(unsigned long, long);
extern void __cdecl w29a_enterCC(void);
extern void __cdecl w29a_leaveCC(void);

long __cdecl w29a_SER_Transmitting(long x)
{
    unsigned char eq;
    char r;
    if (w29a_fgCheck(0, -1) != 0)
        return 0;
    w29a_enterCC();
    eq = (w29a_oq.head == w29a_oq.tail);
    r = (eq == 0);
    w29a_leaveCC();
    return r;
}
