/* _ATFRescued @ rva 0x7f600 (112 B) — v2: byte-twin of _UkraineRescued;
 * shared-true-tail literal = 0x4f76ac "your base." */
extern unsigned short playerDead;   /* =_playerDead */
extern unsigned short playerId;     /* =_playerId */
extern unsigned char forceVictory;  /* =_forceVictory */
extern void __stdcall PushCurObj(unsigned short id);
extern char w34d_chk(void);
extern unsigned char __fastcall Percent(int n);
extern void __stdcall DoDialogInfoBox(const char *msg, int n);
extern void __stdcall PopCurObj(void);
extern char w34d_litB[];  /* map -> _pilotRanks+0x2a4 "You were ... base." */
extern char w34d_litR[];  /* map -> _pilotRanks+0x1f0 "RESCAP patrols ..." */

void w34d_atf(void)
{
    if (playerDead)
        return;
    if (playerId == 0)
        return;
    if (forceVictory)
        return;
    PushCurObj(playerId);
    if (w34d_chk() || Percent(0x23))
        DoDialogInfoBox(w34d_litB, 1);
    else {
        DoDialogInfoBox(w34d_litR, 1);
        playerDead = 2;
    }
    PopCurObj();
}