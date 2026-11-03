// @GRPInHumanWing@4 @ rva 0x5f390 = 390032, 96 B. v2: playerId as WORD
// global (FA: 66 83 3d gate + 66 8b 0d arg load), goto spelling for the
// gate, merged || for the two compare guards (FA's shared false-tail
// branchy bool: je RET0 / jne RET0 / mov al,1).
extern unsigned short playerId;  /* _playerId identity */
extern void __stdcall GRPPartQ(unsigned short id, void *out, int mode);

char __fastcall GRPInHumanWingQ(char *o)
{
    unsigned long r1, r2;
    if (playerId == 0)
        goto L0;
    GRPPartQ(o, &r1, 0);
    GRPPartQ(playerId, &r2, 0);
    if (r1 == -1 || r2 != r1)
        goto L0;
    return 1;
L0:
    return 0;
}