/* w29g _AwardMedal @ 0x662d0 — v1: intrinsified strlen/strcat */
#include <string.h>
extern char w29g_dst[];   /* -> _campaignPilot+0x5af */

void __cdecl w29g_medal_q(char *name)
{
    if (strlen(name) + strlen(w29g_dst) < 1000)
        strcat(w29g_dst, name);
}