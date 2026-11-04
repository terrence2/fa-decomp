/* 0xb8540 (80 B) - unnamed takeoff-flag state chunk:
   (curThing+0x16f & 0x4000) -> SoundOn(stereoSwap+0x70, 0xff, 0xff, 0, curId,
   0x9c4, 0x32, 0,0,0,0,0,0,0, -1); RestoreAutopilot(); tail-jmp
   EnterState(0x12) with ecx=0x12 (b9 12 / e9). 3-B 8d 49 00 pad. */
extern char curThing[];                 /* _curThing @ 0x508738 */
extern char stereoSwap[];               /* _stereoSwap @ 0x4efc98 */
extern unsigned short curId;            /* _curId @ 0x4f2f24 */
extern char __stdcall w43c_sndon(char *s, int f2, int f3, int f4,
    unsigned short a5, int a6, int a7, int f8, int f9, int f10, int f11,
    int f12, int f13, int f14, int f15);  /* ?SoundOn@@YGFPADFFDGFFDFFGGFEF@Z */
extern void __stdcall RestoreAutopilotQ(void);   /* _RestoreAutopilot@0 */
extern void __fastcall EnterState(long n);       /* @EnterState@4 */
void __fastcall w43C_b8540q(void)
{
    if (*(unsigned long *)(curThing + 0x16f) & 0x4000)
        w43c_sndon(stereoSwap + 0x70, 0xff, 0xff, 0, curId, 0x9c4, 0x32,
                   0, 0, 0, 0, 0, 0, 0, -1);
    RestoreAutopilotQ();
    EnterState(0x12);
}
