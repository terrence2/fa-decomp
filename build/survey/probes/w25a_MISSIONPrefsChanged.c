extern unsigned long volatile gamePrefs;
extern unsigned short playerIdW;       /* _playerId interior */
extern unsigned char thisMissionGunsOnly;
extern void __fastcall GetCurObj_q(void);      /* map @4 */
extern void __fastcall PutCurObj(void);
extern void __fastcall HARDUnlimited(void);
extern void __fastcall HARDGunsOnlyAll(void);
extern void __fastcall MISSIONSetCheating(void);

void __fastcall MISSIONPrefsChanged_q(void)
{
    unsigned long g;
    g = gamePrefs;
    if (g & 8) {
        if (playerIdW != 0) {
            GetCurObj_q();
            HARDUnlimited();
            PutCurObj();
            g = gamePrefs;
        }
    }
    if ((g & 0x200000) || thisMissionGunsOnly)
        HARDGunsOnlyAll();
    MISSIONSetCheating();
}
