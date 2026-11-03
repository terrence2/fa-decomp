/* __CreateProMission@0 @ rva 0x7ea60 (112 B) — byte-twin of 0x7e960 except
 * the doScreens-path call targets interior $FA$_t_4225b1 (just past the
 * converted ?MAPOnSpecial chunk). */
extern unsigned char w34d_ds;   /* =_doScreens */
extern char w34d_mn[];          /* =_missionName */
extern char __fastcall LibFileExists(char *s);
extern void __cdecl ErrorExit(const char *f, char *s);
extern char w34d_mapos(void);   /* =$FA$_t_4225b1 */
extern void __cdecl strcpy(char *d, const char *s);

int __stdcall w34d_cpm(void)
{
    if (w34d_ds)
        return w34d_mapos() != 0;
    strcpy(w34d_mn, "~fake.M");
    if (!LibFileExists(w34d_mn))
        ErrorExit("Couldn't find mission file \"%s.\"", w34d_mn);
    return 1;
}