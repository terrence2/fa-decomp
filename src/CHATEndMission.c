// _CHATEndMission@0 @ rva 0x13980 — solo game check, clear chatEditing, rerun
// the init message pair and tail-jmp to MPShellInitMessages (probe w11b_06,
// byte-exact)
extern long numComputers;
extern char chatEditing;
extern void __stdcall MSGInit(void);
extern void __stdcall HUDInitMessages(void);
extern void __stdcall MPShellInitMessages(void);
void __stdcall CHATEndMission_q(void)
{
    if (numComputers == 1)
        return;
    chatEditing = 0;
    MSGInit();
    HUDInitMessages();
    MPShellInitMessages();
}