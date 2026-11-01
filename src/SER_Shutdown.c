// ?SER_Shutdown@@YAXXZ @ rva 0x4c2c0 (25 B code + 7 B pad) — cdecl void:
// gate on ?mpInfo@@3UMP_INFO@@C+0x154, then call Shutdown1/Shutdown2 and
// tail-jmp Shutdown3 (e9):
//   a1 [mp+0x154] / test eax,eax / je ret / call / call / jmp tail / ret.
// Plain C (probe w16c_12 exact) with the +0x154 addend in the C expression
// against the existing bare _mpInfoArr map (double-addend rule).
extern char mpInfoArr[];
extern void SerShutdown1(void);
extern void SerShutdown2(void);
extern void SerShutdown3(void);

void SER_Shutdown(void)
{
    if (*(long *)(mpInfoArr + 0x154) != 0) {
        SerShutdown1();
        SerShutdown2();
        SerShutdown3();
    }
}