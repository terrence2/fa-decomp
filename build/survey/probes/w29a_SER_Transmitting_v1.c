// 0x4b4e0 ?SER_Transmitting@@YAJJ@Z @ 0x44b4e0 (64 B) — v1
// long __cdecl SER_Transmitting(long). FG check short-circuits to return 0;
// inside the critical section r = (head == tail) == 0 held in char bl
// across the Leave call (sete dl / test dl,dl / sete bl double conversion).
struct W29OQ { long head; long tail; };
extern struct W29OQ w29a_oq;                      /* ?OutQueue@@3USERIAL_QUEUE@@A */
extern char __cdecl w29a_fgCheck(unsigned long, long);   /* $FA$_t_4b190 */
extern void __cdecl w29a_enterCC(void);                  /* $FA$_t_4b110 */
extern void __cdecl w29a_leaveCC(void);                  /* $FA$_t_4b170 */

long __cdecl w29a_SER_Transmitting(long x)
{
    char r;
    if (w29a_fgCheck(0xffffffff, 0) != 0)
        return 0;
    w29a_enterCC();
    r = (w29a_oq.head == w29a_oq.tail) == 0;
    w29a_leaveCC();
    return r;
}