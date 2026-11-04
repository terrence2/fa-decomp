/* 0x7bc30 (unnamed, 64 B): sign chooser on int at curThing+0x17f, then
 * word cmp at curThing+0x21, then Percent(0x32) test. a1 moffs form. */
extern char __fastcall w38a_pct(int);   /* @Percent@4 */
extern char _curThing[];                 /* data public */

int w38a_7bc30(void)
{
    int t = *(int *)(_curThing + 0x17f);
    int w = *(short *)(_curThing + 0x21);
    if (t > 0)
        return 1;
    if (t < 0)
        return -1;
    if (w > 0)
        return -1;
    if (w != 0)
        return 1;
    if (w38a_pct(0x32))
        return -1;
    return 1;
}
