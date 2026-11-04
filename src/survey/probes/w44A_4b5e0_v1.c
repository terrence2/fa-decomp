/* ?SER_Read@@YAJJPAEJ@Z 0x4b5e0: buffered serial read loop. latch = rem>limit
   (mpInfo+0x174); loop: ctrl-gate check, w44aSRB chunked read, update
   rem/buf/total; continue while latch && rem>0 && mpInfo+0x14c==0. */
extern long w44amp174;   /* map: ?mpInfo@@3UMP_INFO@@C+0x174 */
extern long w44amp14c;   /* map: ?mpInfo@@3UMP_INFO@@C+0x14c */
extern unsigned char w44aCtrlD;   /* map: ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12d */
extern long __cdecl w44aSRB(long a1, unsigned char *buf, long rem);
   /* map: _w44aSRB=?_SER_Read@@YAJJPAEJ@Z */

long __cdecl w44aSERRead(long a1, unsigned char *buf, long rem)
{
    unsigned long latch = 0;
    long limit = w44amp174;
    long total = 0;

    latch = rem > limit;
    for (;;) {
        long n;
        if (w44aCtrlD == 0)
            return -1;
        n = w44aSRB(a1, buf, rem);
        rem -= n;
        buf += n;
        total += n;
        if (latch && rem > 0) {
            if (w44amp14c == 0)
                continue;
            break;
        }
        break;
    }
    return w44aCtrlD ? total : -1;
}