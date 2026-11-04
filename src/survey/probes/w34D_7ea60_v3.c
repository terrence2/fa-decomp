/* __CreateProMission@0 @ rva 0x7ea60 (112 B) — v3: inverted if so the
 * doScreens body is the out-of-line else-return (FA: test al,al; jne far
 * to the interior $FA$_t_4225b1 call at chunk end, stub t0001d). */
extern unsigned char doScreens;   /* =_doScreens */
extern char missionName[];        /* =_missionName */
extern char __fastcall LibFileExists(char *s);
extern void __cdecl ErrorExit(const char *f, char *s);
extern char w34d_mapos(void);     /* =$FA$_t_4225b1 */
extern char *strcpy(char *d, const char *s);
extern char w34d_litM[];  /* map -> _pilotRanks+0x1c8 ("~fake.M") */
extern char w34d_litE[];  /* map -> _pilotRanks+0x1a4 ("Couldn't ...") */

int __stdcall w34d_cpm(void)
{
    if (!doScreens) {
        strcpy(missionName, w34d_litM);
        if (!LibFileExists(missionName))
            ErrorExit(w34d_litE, missionName);
        return 1;
    }
    return w34d_mapos() != 0;
}