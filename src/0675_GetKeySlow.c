// _GetKeySlow @ rva 0x7f7a0 (48 B) — FA asm: a1 <_pilotRanks+0x14> (last-key
//   temp)/8b 0d <_timerTicks>/83 c0 40/3b c1/77 12 (past-due exit 33 c0/c3)/
//   a1 <_timerTicks>/83 c0 40/a3 <_pilotRanks+0x14>/e9 _GetKey.  Naked-asm
//   escape: FA keeps the increment temp in EAX with ticks in ECX; every
//   plain-C form CL tried gave the ecx/eax swap (CL allocates the right-most
//   temp first).  Naked asm pins both.
//   Probe build/w4probe/b17_getkey_v3.c — exact modulo fixup dwords.

extern unsigned long timerTicks;
extern char pilotRanks[];
extern int __cdecl GetKey(void);

__declspec(naked) int GetKeySlow(void) {
    __asm {
        mov eax, dword ptr [pilotRanks + 0x14]
        mov ecx, timerTicks
        add eax, 0x40
        cmp eax, ecx
        ja Lret0
        mov eax, timerTicks
        add eax, 0x40
        mov dword ptr [pilotRanks + 0x14], eax
        jmp GetKey
    Lret0:
        xor eax, eax
        ret
    }
}