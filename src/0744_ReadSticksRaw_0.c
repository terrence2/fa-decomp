/* @ReadSticksRaw@0 @ rva 0x923d0 (96 B) — fastcall void(void): flag byte
 * masks 1/4/8/0x10 gate four __cdecl ReadDevice(dev) calls; flags reloaded
 * (a1) after every taken call, tests are a8 al,imm; je skips flag-reload
 * too (dead on fallthrough).  Same a1/a8 idiom as @ReadJoystickButtons@0.
 */
extern unsigned long w34E_joyF;   /* =_joystickFunctions */
extern unsigned long w34E_jX;     /* =?joystickXDevice@@3KA */
extern unsigned long w34E_jT;     /* =?joystickThrottleDevice@@3KA */
extern unsigned long w34E_jR;     /* =?joystickRudderDevice@@3KA */
extern unsigned long w34E_jP;     /* =?joystickPOVDevice@@3KA */
extern long __cdecl w34E_rd(unsigned long dev);  /* =?ReadDevice@@YA?AW4JOYRESULT@@K@Z */

void __fastcall ReadSticksRaw(void)
{
    if (w34E_joyF & 1)
        w34E_rd(w34E_jX);
    if (w34E_joyF & 4)
        w34E_rd(w34E_jT);
    if (w34E_joyF & 8)
        w34E_rd(w34E_jR);
    if (w34E_joyF & 0x10)
        w34E_rd(w34E_jP);
}