// ?APEndArrestorCatch@@YAXXZ @ rva 0xb85e0 (48 B) — FA asm: xor ecx,ecx /
//   call @FMHook@4 (fastcall 1-arg extern, id=0) / call _RestoreAutopilot@0 /
//   mov edx,1 / xor ecx,ecx / call @PLANESetThrottle@8 (fastcall, ec=0 dx=1)
//   / mov ecx,0x1a / jmp @EnterState@4 — autopilot end-of-arrestor state
//   hook: silence FMHook, restore autopilot, drop throttle to 0/1, tail-call
//   EnterState(0x1a). Last-statement fastcall call from a cdecl void fn
//   produces the e9 tail (T_InitFarmProc form); fastcall callees pop their
//   own register args so nothing needs cleaning after the jmp.
// Plain C exact (probe b19c_apend; tail 14 B = census leal-leal).
extern void __fastcall FMHook(long id);
extern void __stdcall RestoreAutopilot(void);
extern void __fastcall PLANESetThrottle(long zero, long throttle);
extern void __fastcall EnterState(long state);

void __cdecl APEndArrestorCatch(void)
{
    FMHook(0);
    RestoreAutopilot();
    PLANESetThrottle(0, 1);
    EnterState(0x1a);
}