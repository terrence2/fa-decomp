// @GRPInHumanWing@4 @ rva 0x5f390 = 390032, 96 B.
extern unsigned long playerId;  /* _playerId word global: FA 66 83 3d [g],0 */
extern void __stdcall GRPPartQ(unsigned short id, void *out, int mode); /* _GRPPart@12 identity */

char __fastcall GRPInHumanWingQ(char *o)
{
    unsigned long r1, r2;
    if (playerId == 0)
        return 0;
    GRPPartQ(o, &r1, 0);
    GRPPartQ(playerId, &r2, 0);
    if (r1 == 0xffffffffL)
        return 0;
    if (r2 != r1)
        return 0;
    return 1;
}