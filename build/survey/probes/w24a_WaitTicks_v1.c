extern int __fastcall WaitUntil(unsigned long t);
extern unsigned long timerTicks;

void __fastcall WaitTicks(int d)
{
    int t = timerTicks + d;
    WaitUntil(t);
}
