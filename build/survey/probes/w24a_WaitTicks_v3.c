extern int __fastcall WaitUntil(unsigned long t);
extern unsigned long timerTicks;

void __fastcall WaitTicks(volatile int d)
{
    volatile int t = timerTicks + d;
    WaitUntil(t);
}
