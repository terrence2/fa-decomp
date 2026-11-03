/* __CreateProMission@0 @ rva 0x7ea60 (112 B) — byte-twin of 0x7e960; the
 * doScreens-path call targets interior $FA$_t_4225b1 (stub t0001d). */
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
    if (doScreens)
        return w34d_mapos() != 0;
    strcpy(missionName, w34d_litM);
    if (!LibFileExists(missionName))
        ErrorExit(w34d_litE, missionName);
    return 1;
}