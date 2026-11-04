/* _CanBackUp @ 0x843a0 (144 B): can-this-computer-back-out check.
 * char __stdcall CanBackUp(void):
 *   if (!thisComputer) return 1;                    [85 c0 / b0 01]
 *   switch (curScreen /* short @ 0x51c300, movsx a0*\/) {
 *     case 12: goto Lend;                           [83 f8 0c 74 2e]
 *     case 13: goto Lbrief;                         [83 f8 0d 74 1a]
 *     case 14: if (!doSelectPlane) goto Lbrief; return 1;
 *                                                   [83 f8 0e 74 06]
 *     default: return 0;                            [32 c0]
 *   }
 *   Lbrief: if (!doBriefMap) goto Lend; return 1;
 *   Lend:   RMChangeType(missionName, pmapCalled+0x1924, local);
 *                                                   [push &local; push 0x4f2880; push 0x4f7108]
 *           if (!doBriefPaper) return 0;
 *           if (!RMAccess(local, 0)) return 0;      [push 0x0; push &local]
 *           RMFree(local);                          [push &local]
 *           return 1;
 * local is 16 B (sub esp,0x10); all three calls pass &local[0].
 * w46g_pm is a fake extern for the _pmapCalled+0x1924 literal (0x4f2880).
 */
extern unsigned long thisComputer;          /* _thisComputer */
extern short curScreen;                     /* _curScreen */
extern unsigned char doSelectPlane;         /* _doSelectPlane */
extern unsigned char doBriefMap;            /* _doBriefMap */
extern unsigned char doBriefPaper;          /* _doBriefPaper */
extern char missionName[];                  /* _missionName */
extern char w46g_pm[];                      /* _pmapCalled+0x1924 */
extern void __stdcall RMChangeType(char *a, char *b, void *c);
extern long __stdcall RMAccess(void *h, long a2);
extern void __stdcall RMFree(void *h);

char __stdcall CanBackUp(void)
{
    char local[16];

    if (!thisComputer)
        return 1;
    switch (curScreen) {
    case 12:
        goto Lend;
    case 13:
        goto Lbrief;
    case 14:
        if (!doSelectPlane)
            goto Lbrief;
        return 1;
    default:
        return 0;
    }
Lbrief:
    if (!doBriefMap)
        goto Lend;
    return 1;
Lend:
    RMChangeType(missionName, w46g_pm, local);
    if (!doBriefPaper)
        goto Lfail;
    if (!RMAccess(local, 0))
        goto Lfail;
    RMFree(local);
    return 1;
Lfail:
    return 0;
}