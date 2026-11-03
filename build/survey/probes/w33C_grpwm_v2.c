extern unsigned short playerId;
extern int __stdcall GRPPart(int a, void *b, int c);
extern unsigned char Gb[];    /* -> _groupIds+0x2 */
extern unsigned char Gb0[];   /* -> _groupIds     */

short __stdcall GRPPlayerWM(void)
{
    int r, t, b; unsigned c;
    unsigned short id;

    id = playerId;
    if (id) {
        b = GRPPart(id, &r, 0);
        c = (unsigned char)b;
        if (!c)
            return 0;
        if (c == 1) {
            t = r << 2;
            return *(short *)&Gb[t + (t << 2)];
        }
        if (c == 2) {
            t = r << 2;
            return *(short *)&Gb0[t + (t << 2)];
        }
    }
    return 0;
}