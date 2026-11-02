/* @ReadJoystickButtons@0 @ 0x92ca0 — v2: if-block structure, ret0 as tail */
extern unsigned long w28b_joyFunc;      /* -> _joystickFunctions */
extern unsigned long w28b_joyXDev;      /* -> ?joystickXDevice@@3KA */
extern unsigned char w28b_joyInfo[];    /* -> ?joystickInfo@@3PAUjoyinfo_tag@@A */
extern unsigned long w28b_joyEx[];      /* -> ?joystickInfoEx@@3PAUjoyinfoex_tag@@A */
extern long __cdecl w28b_ReadDev(unsigned long dev);       /* -> ?ReadDevice@@YA?AW4JOYRESULT@@K@Z */
extern long __cdecl w28b_GetJoyTyp(unsigned long dev);     /* -> ?GetJoystickType@@YA?AW4JOYRESULT@@K@Z */

unsigned long __fastcall w28b_rjb_f(void)
{
    if (w28b_joyFunc & 3) {
        w28b_ReadDev(w28b_joyXDev);
        if (w28b_GetJoyTyp(w28b_joyXDev))
            return w28b_joyEx[w28b_joyXDev * 13];
        return *(unsigned long *)(w28b_joyInfo + w28b_joyXDev * 16);
    }
    return 0;
}
