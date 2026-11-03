extern unsigned short playerId;
extern int __stdcall GRPPart(int a, void *b, int c);
extern int G1;   /* -> _groupIds+0x2 */
extern int G0;   /* -> _groupIds   */

short __stdcall GRPPlayerWM(void)
{
    int r, t; unsigned c;

    if (playerId) {
        r = GRPPart(playerId, &r, 0);
        c = (unsigned char)r;
        if (!c)
            return 0;
        if (c == 1) {
            t = r << 2;
            return *(short *)(G1 + t + (t << 2));
        }
        if (c == 2) {
            t = r << 2;
            return *(short *)(G0 + t + (t << 2));
        }
    }
    return 0;
}