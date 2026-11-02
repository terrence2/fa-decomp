// w26a_659e0 @ rva 0x659e0 (416160, unnamed 16 B orphan) — FA bytes (raw
// cross-check; dis.py hides nothing here but the tail is census pad):
//   66 85 c9            test cx,cx
//   74 05               je  L0 (short, target = the ret at +0x0a)
//   e9 06 00 00 00      jmp $FA$_t_4659f0   (rel32 -> gap chunk @0x659f0)
// L0: c3                ret
//   05 00 00 00 00      (5 B tail pad, census "0500000000")
// i.e. fastcall-gate tail-jmp into the unnamed continuation chunk at
// 0x659f0. The $FA$_t gap anchor is not addressable at C level, so the
// target goes through a C extern renamed by --map (wave-21 recipe).
// Pure naked asm (C cannot order je-before-jmp with a shared trailing ret).
extern void gap659f0(void);   /* $FA$_t_4659f0: continuation chunk @0x659f0 */
__declspec(naked) void w26a_659e0(void)
{
    __asm {
        test cx, cx
        je short  L0
        jmp       gap659f0
L0:     ret
    }
}