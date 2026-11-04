/* __CreateQuickMission@4 @ rva 0x7e9d0 (112 B) -- v1 plain C, stdcall(int).
 * !doScreens: inline strcpy(missionName, pilotRanks+0x1c8); if the
 * LibFileExists(missionName) byte fails -> ErrorExit(pilotRanks+0x1a4,
 * missionName); return 1. Else: return (char)QuickMission(a1). */
#include <string.h>

extern char doScreens;
extern char missionName[];
extern char pilotRanks[];
extern char __fastcall LibFileExists(char *name);
extern void ErrorExit(char *a, char *b);
extern char __stdcall QuickMission(int a);

int __stdcall _CreateQuickMission(int a1)
{
    if (doScreens == 0) {
        strcpy(missionName, &pilotRanks[0x1c8]);
        if (LibFileExists(missionName) == 0)
            ErrorExit(&pilotRanks[0x1a4], missionName);
        return 1;
    }
    return (signed char)QuickMission(a1);
}