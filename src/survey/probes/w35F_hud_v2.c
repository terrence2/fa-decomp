/* w35F ?HUDSetStability@@YIJXZ @ 0xaa00 — v2 (post-div test + short dv in si)
 * FA: 66 a1 <curThing+0x1f>; push esi; 66 be b6 00 (si=0xb6); xor ecx,ecx;
 * cwd; idiv si; test ax,ax; jle; mov ecx,eax; call @Abs@4; cdq;
 * mov ecx,0x14; idiv ecx; mov ecx,eax; then the v1-matching dam/20c/clamp tail */
extern int __fastcall w35f_absq(short);  /* -> @Abs@4 */
extern char curThing[];                  /* bare public _curThing */
extern char dam[];                       /* bare public _dam */

int __fastcall w35f_hud(void)
{
    short q;
    short dv;
    short r;
    int a;
    q = *(short *)(curThing + 0x1f);
    dv = 182;
    a = 0;
    r = q / dv;
    if (r > 0)
        a = w35f_absq(r) / 20;
    {
        short m = (short)(*(short *)(dam + 4) / 2);
        if (m < *(short *)(dam + 2))
            a += 2;
    }
    if (*(char *)(curThing + 0x20c) == 2)
        a += 2;
    if (a > 4)
        a = 4;
    return a;
}