/* _UkraineRescued @ rva 0x7f4b0 (112 B) — cdecl void(void):
 * if (_playerDead) return; if (_playerId==0) return; if (_forceVictory)
 * return; PushCurObj(_playerId); if (chk(0x47f520)() || Percent(0x23))
 * [shared out-of-line]: DoDialogInfoBox(lit2,1); else:
 * DoDialogInfoBox(lit1,1); _playerDead = 2; both tails tail-jmp PopCurObj.
 * NOTE: FA sets _playerDead=2 INSIDE the else fall-through only. */
extern unsigned short w34d_pd;   /* =_playerDead */
extern unsigned short w34d_pid;  /* =_playerId */
extern unsigned char w34d_fv;    /* =_forceVictory */
extern void __stdcall PushCurObj(unsigned long id);
extern char w34d_chk(void);
extern unsigned char __fastcall Percent(int n);
extern void __stdcall DoDialogInfoBox(const char *msg, int n);
extern void __stdcall PopCurObj(void);

void w34d_ukr(void)
{
    if (w34d_pd)
        return;
    if (w34d_pid == 0)
        return;
    if (w34d_fv)
        return;
    PushCurObj(w34d_pid);
    if (w34d_chk() || Percent(0x23))
        DoDialogInfoBox("You were promptly picked up by friendly forces and returned to your ship.", 1);
    else {
        DoDialogInfoBox("RESCAP patrols were unable to locate you.  You were reported Missing In Action, and were never found.", 1);
        w34d_pd = 2;
    }
    PopCurObj();
}