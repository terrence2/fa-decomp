extern unsigned short playerId;
extern int __stdcall WNGPart(int a, void *b, int c);
extern unsigned char Wb[];    /* -> _wingIds+0x2 */
extern unsigned char Wb0[];   /* -> _wingIds     */

short __stdcall WNGPlayerWM(void)
{
    int r, t, b; unsigned c;
    unsigned short id;

    id = playerId;
    if (id) {
        b = WNGPart(id, &r, 0);
        c = (unsigned char)b;
        if (!c)
            return 0;
        if (c == 1) {
            t = r << 2;
            return *(short *)&Wb[t + (t << 2)];
        }
        if (c == 2) {
            t = r << 2;
            return *(short *)&Wb0[t + (t << 2)];
        }
    }
    return 0;
}