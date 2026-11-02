/* _MISSIONPrefsChanged@0 @ 0x84960 (80B) variant A: direct volatile reads */
extern unsigned long volatile gamePrefs;
extern unsigned short playerId;
extern unsigned char thisMissionGunsOnly;
extern void __fastcall GetCurObj_q(void);      /* -> @GetCurObj@4 */
extern void __fastcall PutCurObj(void);
extern void __stdcall HARDUnlimited(void);
extern void __stdcall HARDGunsOnlyAll(void);
extern void __stdcall MISSIONSetCheating(void);

void __fastcall MISSIONPrefsChanged_q(void)
{
    if (gamePrefs & 8) {
        if (playerId != 0) {
            GetCurObj_q();
            HARDUnlimited();
            PutCurObj();
        }
    }
    if ((gamePrefs & 0x200000) || thisMissionGunsOnly != 0)
        HARDGunsOnlyAll();
    MISSIONSetCheating();
}
