/* ?MPStatusInit@@YIXXZ @ rva 0x70460 (64 B) — thiscall void(this):
   four 8-long fills; the value-3 blocks fill DWORDS 0x00000003 (b8 03
   00 00 00), so they are long-array stores, not byte-memset. Try plain
   fill loops and hope CL's store-loop -> rep stosd recognition fires.
   eax=-1 CSE'd over the two -1 fills, eax=3 over the two 3 fills. */
extern long w29e_msd[];    /* =?mpStatus@@3PAJA (+0) */
extern long w29e_msdD[];   /* =?mpStatusToDraw@@3PAJA */

void MPStatusInitW(void)
{
    long i;
    for (i = 0; i < 8; i++) w29e_msdD[i] = -1;
    for (i = 0; i < 8; i++) w29e_msdD[i + 48] = -1;
    for (i = 0; i < 8; i++) w29e_msd[i] = 3;
    for (i = 0; i < 8; i++) w29e_msdD[i + 40] = 3;
}