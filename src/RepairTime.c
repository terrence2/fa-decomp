// ?RepairTime@@YIJJ@Z @ rva 0x539c0 (32 B) — FA asm:
//   b8 <_rudder+0x1570>      mov eax, entry-table base (imm32, abs fixup)
//   8b 50 08 / 3b d1 / 74 0d scan: edx=[e+8], cmp edx,ecx (fastcall key), je found
//   83 c0 0c                 e += 0xc (12-byte entries)
//   3d <_rudder+0x1624>      cmp eax, end imm32 (abs fixup #2)
//   72 ef                    jb scan (unsigned)
//   33 c0 / c3               default: return 0
//   found: 8b 40 04 / c3     return [e+4]
// 15-entry (0xb4/0xc) table inside the _rudder data block (0x540a30); both
// imm32s are interior field offsets — offset lives in the C expression only
// (wave-12 double-addend rule), array decay gives the b8-imm32 + DIR32 form.
// Unsigned compare from the unsigned long locals; plain C is exact
// (probe b18c_RepairTime2; round 1 with a cached `end` local held it in edx
// and forced a dead push ebx — the rematerialized end imm32 frees edx and
// CL then drops the push).
extern char rudder[];

unsigned long __fastcall RepairTime(int key, int arg)
{
    unsigned long e = (unsigned long)(rudder + 0x1570);
    for (;;) {
        if (*(int *)(e + 8) == key)
            return *(int *)(e + 4);
        e += 0xc;
        if (e >= (unsigned long)(rudder + 0x1624))
            return 0;
    }
}
