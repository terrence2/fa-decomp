// w24b_chunkdf870 @ rva 0xdf870 (914864, unnamed gap, 11 B) — FA bytes:
//   6a 02            push 2
//   e8 b9 69 ff ff   call __amsg_exit (rel32 -> chunk 0xd6230... FA 0x4d6230)
//   83 c4 04         add esp,4
//   c3               ret
// Pure CL C — EXACT fit (code 0xb, no pad), byte-verify PASS, no tail-accept.
// CL /c /O2 /Gy /G5 emits this verbatim for a cdecl 1-arg void call.
// Provenance: toolchain-diff rel32 call target __amsg_exit is FA's own text
// chunk, resolved by name (C-level `_amsg_exit` decorates to obj `__amsg_exit`
// = FA chunk name; no map needed).
extern void _amsg_exit(int n);
void w24b_chunkdf870(void) { _amsg_exit(2); }
