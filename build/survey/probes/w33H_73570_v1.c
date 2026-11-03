/* rva 0x73570 (48 B): a1 moffs loads dword at _curThing+0x1; test ah,0x20;
 * jne ret; else Kill(); Rand(2) -> movsx ecx,ax; inc; tail-jmp
 * @MANRunAway@4 (fastcall). No prolog at all (fpo/esp). */
extern unsigned long thng2;             /* -> _curThing+0x1 */
extern void Kill(void);                 /* _Kill@0 */
extern int __fastcall Rand(int n);      /* @Rand@4 */
extern void __fastcall MANRunAway(int n); /* @MANRunAway@4 */

void __fastcall w33h_73570(void)
{
    if ((thng2 & 0x2000u) == 0) {
        Kill();
        MANRunAway(Rand(2) + 1);
    }
}
