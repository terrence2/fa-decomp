// _InitChain@0 @ rva 0x617c0 (32 B) — zeros chainStart (word),
// correctChainPlacement+0x1c, serviceTicks+0x8 (word), eventFilterProc.
// Leading word store makes CL materialize xor eax,eax then 66 a3 / a3 /
// 66 a3 / a3 (CPClearMissile pattern). probe w12a_13 matched w/ masked
// fixups; offsets live in the C, NOT the map TOs (double addend).
extern char chainStartArr[];
extern char chainCorrectArr[];
extern char chainTicksArr[];
extern long eventFilterProc;

void __stdcall InitChain_q(void)
{
    *(unsigned short *)(chainStartArr + 0) = 0;
    *(long *)(chainCorrectArr + 0x1c) = 0;
    *(unsigned short *)(chainTicksArr + 0x8) = 0;
    eventFilterProc = 0;
}
