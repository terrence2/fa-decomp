/* w40D_b6db0 v2: char* arithmetic for the +0xba flags load (pointer
 * scaling bug fix) and pointer-typed 1st Dist arg so CL folds the
 * push (FA: push imm32 _curThing+0x11, not b8/add/push).
 */
typedef unsigned char uchar;

extern unsigned long curThing;   /* 0x508738 */

int __stdcall Dist(char *, int);         /* -> _Dist@8 */
char __fastcall w40d_chk6(void);         /* -> @w40d_chk6@0 */

int __fastcall APTakeoffType(char *ctl, char *obj)
{
    int f;
    uchar m;
    f = *(int *)((char *)(*(int **)(ctl + 5)) + 0xba);
    if (obj == (char *)0)
        return -1;
    if (*(obj + 0xe8) && !(f & 0x40))
        return -1;
    if (f & 0x08)
        return 0xa;
    if (*(obj + 0xe9) && (f & 0x02))
        return 7;
    if (f & 0x20)
    {
        if (*(obj + 0xeb))
            return 0xd;
        if (w40d_chk6())
            return 0xd;
        if (Dist((char *)&curThing + 0x11,
                 *(int *)((char *)&curThing + 0x231) + 0xaa) > 0x1db00)
            return 0xa;
    }
    m = *(uchar *)(obj + 0xec);
    if (m < 1)
        return -1;
    return 0x11;
}