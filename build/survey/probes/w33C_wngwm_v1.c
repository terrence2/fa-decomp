extern unsigned short playerId;
extern int __stdcall WNGPart(int a, void *b, int c);
extern int W1;   /* -> _wingIds+0x2 */
extern int W0;   /* -> _wingIds   */

short __stdcall WNGPlayerWM(void)
{
    int r, t; unsigned c;

    if (playerId) {
        r = WNGPart(playerId, &r, 0);
        c = (unsigned char)r;
        if (!c)
            return 0;
        if (c == 1) {
            t = r << 2;
            return *(short *)(W1 + t + (t << 2));
        }
        if (c == 2) {
            t = r << 2;
            return *(short *)(W0 + t + (t << 2));
        }
    }
    return 0;
}