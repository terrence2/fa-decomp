extern unsigned short playerId;
extern int __stdcall GRPPart(int a, void *b, int c);
extern unsigned char Gb[];    /* -> _groupIds+0x2 */
extern unsigned char Gb0[];    /* -> _groupIds     */

short __stdcall GRPPlayerWM(void)
{
    unsigned short id;
    int r, b, t;

    id = playerId;
    if (id == 0)
        goto L0;
    b = GRPPart(id, &r, 0);
    switch ((unsigned char)b) {
    case 0:
        return 0;
    case 1:
        t = r << 2;
        return *(short *)&Gb[t + (t << 2)];
    case 2:
        t = r << 2;
        return *(short *)&Gb0[t + (t << 2)];
    }
L0:
    return 0;
}