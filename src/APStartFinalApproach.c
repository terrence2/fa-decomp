// ?APStartFinalApproach@@YAXXZ @ rva 0xb85b0 (48 B) — void
// APStartFinalApproach(void): ask @APLandingType@8 (ecx=&curThing,
// edx=*(int*)(curThing+0x231) via moffs field read) for the final-approach
// landing type; 0x18 => EnterState(0x18) else EnterState(0x15), both as
// fastcall tail jmps @EnterState@4 (duplicated tails). Plain-C probe.
extern char curThing[];
extern int curThing231;          /* the dword at _curThing+0x231 */
extern int __fastcall APLandingTypeQ(void *a, int b);   /* @APLandingType@8 */
extern void __fastcall EnterStateQ(int s);              /* @EnterState@4 */

void apsfaq(void)
{
    if (APLandingTypeQ(&curThing, curThing231) == 0x18)
        EnterStateQ(0x18);
    else
        EnterStateQ(0x15);
}