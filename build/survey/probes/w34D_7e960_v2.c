/* __SingleMission@0 @ rva 0x7e960 (112 B) — v2: strcpy decl returns char*
 * (C2371 fix), literals as named externs (map to _pilotRanks deltas;
 * strAbort precedent keeps CL's literal bytes out of the link). */
extern unsigned char doScreens;   /* =_doScreens */
extern char missionName[];        /* =_missionName */
extern char __fastcall LibFileExists(char *s);
extern void __cdecl ErrorExit(const char *f, char *s);
extern int __stdcall SingleMission(void);
extern char *strcpy(char *d, const char *s);
extern char w34d_litM[];  /* map -> _pilotRanks+0x1c8 ("~fake.M") */
extern char w34d_litE[];  /* map -> _pilotRanks+0x1a4 ("Couldn't ...") */

int __stdcall w34d_singm(void)
{
    if (doScreens)
        return SingleMission() != 0;
    strcpy(missionName, w34d_litM);
    if (!LibFileExists(missionName))
        ErrorExit(w34d_litE, missionName);
    return 1;
}