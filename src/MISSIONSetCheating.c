// _MISSIONSetCheating@0 @ rva 0x7f0f0 (49 B code + 12 B 05/8da424 pad) —
// three guarded byte stores of 1 to _playerCheating (c6 05, elided by
// dis.py), tests: a9 imm32 on gamePrefs (0x20069, a1 first-read moffs),
// f6 c5 30 byte-fold on gameMultiPrefs (mask 0x3000 -> test ch, 8b 0d
// second-read moffs), a9 reusing the SAME eax from the first load (0x180).
// Plain C: gamePrefs kept in a named local g (pins eax across all three
// tests); gameMultiPrefs read in-place. CL 10.20 emits a1/a9/f6-c5/8b 0d/
// c6 05 naturally from this spell.
extern unsigned char playerCheating;    /* _playerCheating */
extern unsigned long gamePrefs;         /* _gamePrefs */
extern unsigned long gameMultiPrefs;    /* _gameMultiPrefs */

void MISSIONSetCheating_q(void)
{
    unsigned long g = gamePrefs;

    if (g & 0x20069)
        playerCheating = 1;
    if (gameMultiPrefs & 0x3000)
        playerCheating = 1;
    if ((g & 0x180) == 0)
        playerCheating = 1;
}