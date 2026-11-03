/* __SingleMission@0 @ rva 0x7e960 (112 B) — stdcall wrapper:
 * if (_doScreens) return SingleMission() != 0 (cmp al,1 / sbb / inc);
 * inline strcpy of the "~fake.M" literal (scasb strlen + rep movs) into
 * _missionName; if !LibFileExists(_missionName) ErrorExit("Couldn't find
 * mission file \"%s.\"", _missionName) (cdecl); return 1. */
extern unsigned char w34d_ds;   /* =_doScreens */
extern char w34d_mn[];          /* =_missionName */
extern char __fastcall LibFileExists(char *s);
extern void __cdecl ErrorExit(const char *f, char *s);
extern int __stdcall SingleMission(void);
extern void __cdecl strcpy(char *d, const char *s);

int __stdcall w34d_singm(void)
{
    if (w34d_ds)
        return SingleMission() != 0;
    strcpy(w34d_mn, "~fake.M");
    if (!LibFileExists(w34d_mn))
        ErrorExit("Couldn't find mission file \"%s.\"", w34d_mn);
    return 1;
}