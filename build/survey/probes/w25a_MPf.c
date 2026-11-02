/* variant F: assignment-expression keeps w live for the whole gated block */
extern unsigned long volatile gamePrefs;
extern unsigned short playerId;
extern unsigned char thisMissionGunsOnly;
extern void __fastcall GetCurObj_q(unsigned short w);
extern void __fastcall PutCurObj(void);
extern void __stdcall HARDUnlimited(void);
extern void __stdcall HARDGunsOnlyAll(void);
extern void __stdcall MISSIONSetCheating(void);

void __fastcall MISSIONPrefsChanged_q(void)
{
    unsigned short w;
    if (gamePrefs & 8) {
        if ((w = playerId) != 0) {
            GetCurObj_q(w);
            HARDUnlimited();
            PutCurObj();
        }
    }
    if ((gamePrefs & 0x200000) || thisMissionGunsOnly != 0)
        HARDGunsOnlyAll();
    MISSIONSetCheating();
}
