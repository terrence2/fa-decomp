/* w41B 0x271e0 v2: while(q[0]==0) loop (entry check = FA's 80 3d form),
 * staged r with shared exit (FA's found path jmps to the shared pop/ret). */
extern char w41bFly[];   /* -> ?mcFlyAll@@3DA+0x34 */

unsigned short __fastcall w41bFlyFind(char *p)
{
    unsigned short r;
    char *q;

    q = w41bFly;
    while (q[0] == 0) {
        if (*(unsigned short *)(q + 6) == *(unsigned short *)(p + 0x1a)
            && *(unsigned short *)(p + 0x1c) == *(unsigned short *)(q + 8)
            && *(unsigned short *)(p + 0x1e) == *(unsigned short *)(q + 0xa)) {
            r = (unsigned short)((int)(q - w41bFly) / 14);
            goto RET;
        }
        q = q + 14;
    }
    r = 0;
RET:
    return r;
}