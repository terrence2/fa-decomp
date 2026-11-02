// 0x4b4e0 ?SER_Transmitting@@YAJJ@Z @ 0x44b4e0 — v3 (pre-bool)
// eq = (head == tail); then r = !eq: CL materializes the inner sete in
// dl (register-held char, no memory) and re-tests it -> cmp / sete dl /
// test dl,dl / sete bl — FA's double conversion.
struct W29OQ { long head; long tail; };
extern struct W29OQ w29a_oq;
extern char __cdecl w29a_fgCheck(unsigned long, long);
extern void __cdecl w29a_enterCC(void);
extern void __cdecl w29a_leaveCC(void);

long __cdecl w29a_SER_Transmitting(long x)
{
    char eq, r;
    if (w29a_fgCheck(0, -1) != 0)
        return 0;
    w29a_enterCC();
    eq = (w29a_oq.head == w29a_oq.tail) != 0;
    r = !eq;
    w29a_leaveCC();
    return r;
}