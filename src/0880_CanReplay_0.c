// _CanReplay@0 @ rva 0xa2810 — no mission named, or a solo game: no replay
extern char missionName[];
extern long numComputers;
char __stdcall CanReplay_q(void)
{
    if (missionName[0] == 0)
        return 0;
    return numComputers <= 1;
}
