/* v2: thng2 needs a map (_curThing+0x1); Rand declared short-return so the
 * +1 stages movsx ecx,ax; inc ecx (n+1 with n short = inc, not lea-fold). */
extern unsigned long thng2;               /* -> _curThing+0x1 */
extern void Kill(void);                   /* _Kill@0 */
extern short __fastcall Rand(int n);      /* @Rand@4 */
extern void __fastcall MANRunAway(int n); /* @MANRunAway@4 */

void __fastcall w33h_73570(void)
{
    short n;
    if ((thng2 & 0x2000u) == 0) {
        Kill();
        n = Rand(2);
        MANRunAway(n + 1);
    }
}
