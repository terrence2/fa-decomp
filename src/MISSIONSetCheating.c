// _MISSIONSetCheating@0 @ rva 0x7f0f0 (49 B code + 12 B 05/8da424 pad) —
// three guarded byte stores of 1 to _playerCheating (c6 05, elided by
// dis.py), tests: a9 imm32 on gamePrefs (0x20069), f6 c5 30 byte-fold on
// gameMultiPrefs (mask 0x3000 -> test ch), a9 again reusing the SAME eax
// from the first load (0x180).  MASM gives a1 load, a9 tests, test ch
// naturally; je/jne +7 skips land on the next test exactly as FA.
extern unsigned char playerCheating;    /* _playerCheating */
extern unsigned long gamePrefs;         /* _gamePrefs */
extern unsigned long gameMultiPrefs;    /* _gameMultiPrefs */

void __declspec(naked) __stdcall MISSIONSetCheating_q(void)
{
    __asm {
        mov  eax, gamePrefs
        test eax, 020069h
        je   L1
        mov  byte ptr playerCheating, 1
    L1: mov  ecx, gameMultiPrefs
        test ch, 030h
        je   L2
        mov  byte ptr playerCheating, 1
    L2: test eax, 0180h
        jne  L3
        mov  byte ptr playerCheating, 1
    L3: ret
    }
}