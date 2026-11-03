/* _ATFRescued @ rva 0x7f600 (112 B) — byte-twin of _UkraineRescued; only
 * the shared-true-tail literal differs (0x4f76ac "your base."). */
extern unsigned short w34d_pd;   /* =_playerDead */
extern unsigned short w34d_pid;  /* =_playerId */
extern unsigned char w34d_fv;    /* =_forceVictory */
extern void __stdcall PushCurObj(unsigned long id);
extern char w34d_chk(void);
extern unsigned char __fastcall Percent(int n);
extern void __stdcall DoDialogInfoBox(const char *msg, int n);
extern void __stdcall PopCurObj(void);

void w34d_atf(void)
{
    if (w34d_pd)
        return;
    if (w34d_pid == 0)
        return;
    if (w34d_fv)
        return;
    PushCurObj(w34d_pid);
    if (w34d_chk() || Percent(0x23))
        DoDialogInfoBox("You were promptly picked up by friendly forces and returned to your base.", 1);
    else {
        DoDialogInfoBox("RESCAP patrols were unable to locate you.  You were reported Missing In Action, and were never found.", 1);
        w34d_pd = 2;
    }
    PopCurObj();
}