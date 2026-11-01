// _TIMERestart@0 @ rva 0x84be0 — mov eax,[_timerTicks] / mov
//   [_lastTicks],eax / ret; CL picks the a1/a3 moffs pair for the eax
//   round-trip between globals (probe w5_timer exact).
extern long timerTicks, lastTicks;

void __stdcall TIMERestart(void)
{
    lastTicks = timerTicks;
}
