// _GetPlayerControl@0 @ rva 0x17610 (95760, 80 B) — stdcall void(void):
//   call @ReadSticksRaw@0 / {push 1 / mov eax,[dev] / push 2 / call
//   [deviceProcs+eax*4] / add esp,8} x3 (stick/rudder/throttle) /
//   push 0 / push 2 / call ?KeyStick@@YAGFG@Z (cdecl shape: add esp,8) / ret.
extern void __fastcall w27c_rsr(void);              /* =@ReadSticksRaw@0 */
extern int w27c_stickDev;                           /* =_stickDevice */
extern int w27c_rudderDev;                          /* =_rudderDevice */
extern int w27c_throttleDev;                        /* =_throttleDevice */
extern short (__cdecl *w27c_devProcs[])(short, unsigned short);
                                                    /* =?deviceProcs@@3PAP6AFFF@ZA */
extern short __cdecl w27c_KeyStick(short a, unsigned short b);
                                                    /* =?KeyStick@@YAGFG@Z */

void __stdcall w27c_GetPlayerControl(void)
{
    w27c_rsr();
    w27c_devProcs[w27c_stickDev](2, 1);
    w27c_devProcs[w27c_rudderDev](2, 1);
    w27c_devProcs[w27c_throttleDev](2, 1);
    w27c_KeyStick(2, 0);
}
