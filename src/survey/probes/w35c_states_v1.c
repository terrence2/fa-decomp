// w35C #4: unnamed 64-B state-set chunk @ rva 0xb8380 — six fastcall calls
// (0/0 or single 0 args, PLANESetThrottle(0x64,0)) then the tail-jmp
// EnterState(0x1f). No frame, no saved regs.
extern void __fastcall SetAutopilot(int a, int b);
extern void __fastcall FMGear(int a);
extern void __fastcall FMFlaps(int a, int b);
extern void __fastcall FMHook(int a);
extern void __fastcall PLANESetThrottle(int a, int b);
extern void __fastcall FMVector(int a, int b);
extern void __fastcall EnterState(int st);

void __cdecl Chunk_b8380(void)
{
    SetAutopilot(0, 0);
    FMGear(0);
    FMFlaps(0, 0);
    FMHook(0);
    PLANESetThrottle(0x64, 0);
    FMVector(0, 0);
    EnterState(0x1f);
}