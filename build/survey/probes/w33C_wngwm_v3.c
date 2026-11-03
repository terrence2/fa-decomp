extern unsigned short playerId;
extern int __stdcall WNGPart(int a, void *b, int c);
extern unsigned char Wb[];    /* -> _wingIds+0x2 */
extern unsigned char Wb0[];   /* -> _wingIds     */

short __stdcall WNGPlayerWM(void)
{
    int r, b, t;

    if (playerId) {
        b = WNGPart(playerId, &r, 0);
        switch ((unsigned char)b) {
        case 0:
            return 0;
        case 1:
            t = r << 2;
            return *(short *)&Wb[t + (t << 2)];
        case 2:
            t = r << 2;
            return *(short *)&Wb0[t + (t << 2)];
        }
    }
    return 0;
}