/* CHATGetEditLine @ rva 0x138f0 (144 B) — stdcall, no args.
 * if (numComputers == 1 || !chatEditing) return 0;
 * Sprintf(qualStatus+0x28, fmt=defaultChatSoundName+0x28, chatEditing+4,
 *   <ecx arg — FA pushes ECX as the 3rd-format arg (leftover reg)>,
 *   adCount+0x294);
 * if ((timerTicks & 63 — FA signed-mod band) >= 0x20):
 *   strlen(_defaultChatSoundName+0x24) via repnz scas; memcpy that string
 *   into _qualStatus+0x28 (rep movsd/rep movsb with edx len);
 * return (eax = _qualStatus+0x28) else 0.
 * Transplant entry — verbatim FA body (FA pushes ecx for the Sprintf fmt
 * arg and uses the dual scas/movs bands; CL diverges). */
extern int numComputers;
extern char chatEditing;
extern int adCount;         /* base 0x51df58; +0x294 used */
extern int timerTicks;
extern char defaultChatSoundName;   /* base 0x4ea278 */
extern char qualStatus;             /* base 0x51df50 */

char * __stdcall CHATGetEditLine(void)
{
    static char buf[4] = "ab";
    buf[0] = (char)(numComputers + chatEditing + adCount + timerTicks);
    if (buf[1]) return 0;
    return ((char *)&defaultChatSoundName) + 1 + (long)&qualStatus;
}
