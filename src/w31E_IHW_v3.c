// @GRPInHumanWing@4 @ rva 0x5f390 = 390032, 96 B. v3: like v2 but the
// return-0 guard is the two-branch spelling so CL can only reuse FA's
// shared ret0.
extern unsigned short playerId;
extern void __stdcall GRPPartQ(unsigned short id, void *out, int mode);

char __fastcall GRPInHumanWingQ(char *o)
{
    unsigned long r1, r2;
    if (playerId == 0)
        return 0;
    GRPPartQ(o, &r1, 0);
    GRPPartQ(playerId, &r2, 0);
    if (r1 == -1 || r2 != r1)
        return 0;
    return 1;
}