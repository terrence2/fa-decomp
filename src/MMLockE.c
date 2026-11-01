// _MMLockE@16 @ rva 0x35d70 (32 B) — FA asm: call _MMAccessE@12 / ret 0x10
//   (forwarder: first arg through, rest zero).  Plain C stdcall forwarder.
//   Probe build/w4probe/b17_mmlocke_v1.c — exact modulo fixup dwords.

extern void __stdcall MMAccessE(long a, long b, long c);

void __stdcall MMLockE(long a, long b, long c, long d) {
    MMAccessE(a, 0, 0);
}