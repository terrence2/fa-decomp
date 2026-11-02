extern unsigned char __stdcall GRPPart_q(unsigned long a, unsigned long *out, unsigned long z);
extern unsigned char grpSizesB[];   /* -> _groupSizes */
extern unsigned long grpDwBase[];   /* -> _groupIds+0x2 */

struct GRP16 { unsigned long wId; unsigned long p1, p2, p3; };
extern struct GRP16 grpRecsW[];     /* -> _groupIds+0x2 */

unsigned short __fastcall GRPWingman_q2(unsigned long a)
{
    unsigned long out[1];
    if (GRPPart_q(a, out, 0) != 1)
        return 0;
    if (grpSizesB[out[0]] < 2)
        return 0;
    return (unsigned short)grpRecsW[out[0]].wId;
}
