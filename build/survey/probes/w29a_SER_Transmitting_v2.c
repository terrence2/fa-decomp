// 0x4b4e0 ?SER_Transmitting@@YAJJ@Z @ 0x44b4e0 — v2
// FA pushes 6a ff then 6a 00 => arg2 (long, -1) evaluated first
// (right-to-left), arg1 = 0. The bool is !(head == tail): the ! forces
// CL to materialize the inner sete in dl and re-test (sete dl / test
// dl,dl / sete bl), then char bl survives the Leave call (movsx eax,bl).
struct W29OQ { long head; long tail; };
extern struct W29OQ w29a_oq;
extern char __cdecl w29a_fgCheck(unsigned long, long);
extern void __cdecl w29a_enterCC(void);
extern void __cdecl w29a_leaveCC(void);

long __cdecl w29a_SER_Transmitting(long x)
{
    char r;
    if (w29a_fgCheck(0, -1) != 0)
        return 0;
    w29a_enterCC();
    r = !(w29a_oq.head == w29a_oq.tail);
    w29a_leaveCC();
    return r;
}