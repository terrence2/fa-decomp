// w24b_chunkd5fa0 @ rva 0xd5fa0 (876448, unnamed gap, 11 B) — FA bytes:
//   6a 01            push 1
//   e8 09 00 00 00   call $FA$_t_4d5fb0 (rel32 -> gap anchor, chunk @0xd5fb0)
//   83 c4 04         add esp,4
//   c3               ret
// i.e. gap-helper(1). Pure CL C — EXACT fit (code 0xb, no pad), byte-verify
// PASS, no tail-accept. The $FA$_t gap anchor is NOT addressable at C level,
// so the call goes through a C-level extern `gap235fb0` renamed by fitobj
// --map (wave-21 --alias $FA$ anchors recipe). fitobj resolves it to the
// chunk-start stub symbol defined by the 0xd5fb0 stub object.
// Provenance: toolchain-diff rel32 target $FA$_t_4d5fb0 (FA gap chunk).
extern void gap235fb0(int n);
void w24b_chunkd5fa0(void) { gap235fb0(1); }
