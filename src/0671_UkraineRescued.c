/* _UkraineRescued @ rva 0x7f4b0 (112 B) — v2: PushCurObj param declared
 * unsigned short so CL skips the `and eax,0xffff` zero-extension FA lacks
 * (FA pushes the 66-a1 word load straight). */
extern unsigned short playerDead;   /* =_playerDead */
extern unsigned short playerId;     /* =_playerId */
extern unsigned char forceVictory;  /* =_forceVictory */
extern void __stdcall PushCurObj(unsigned short id);
extern char w34d_chk(void);
extern unsigned char __fastcall Percent(int n);
extern void __stdcall DoDialogInfoBox(const char *msg, int n);
extern void __stdcall PopCurObj(void);
extern char w34d_litS[];  /* map -> _pilotRanks+0x258 "You were ... ship." */
extern char w34d_litR[];  /* map -> _pilotRanks+0x1f0 "RESCAP patrols ..." */

void w34d_ukr(void)
{
    if (playerDead)
        return;
    if (playerId == 0)
        return;
    if (forceVictory)
        return;
    PushCurObj(playerId);
    if (w34d_chk() || Percent(0x23))
        DoDialogInfoBox(w34d_litS, 1);
    else {
        DoDialogInfoBox(w34d_litR, 1);
        playerDead = 2;
    }
    PopCurObj();
}