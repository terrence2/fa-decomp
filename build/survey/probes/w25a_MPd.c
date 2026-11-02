/* variant D: playerId volatile global, PLAIN w local (not volatile) */
extern unsigned long volatile gamePrefs;
extern volatile unsigned short playerId;
extern unsigned char thisMissionGunsOnly;
extern void __fastcall GetCurObj_q(void);      /* -> @GetCurObj@4 */
extern void __fastcall PutCurObj(void);
extern void __stdcall HARDUnlimited(void);
extern void __stdcall HARDGunsOnlyAll(void);
extern void __stdcall MISSIONSetCheating(void);

void __fastcall MISSIONPrefsChanged_q(void)
{
    unsigned short w;
    if (gamePrefs & 8) {
        w = playerId;
        if (w != 0) {
            GetCurObj_q();
            HARDUnlimited();
            PutCurObj();
        }
    }
    if ((gamePrefs & 0x200000) || thisMissionGunsOnly != 0)
        HARDGunsOnlyAll();
    MISSIONSetCheating();
}
