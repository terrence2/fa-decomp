// w24b_chunke2ce0 @ rva 0xe2ce0 (928992, unnamed gap, 9 B) — FA bytes:
//   e8 6b 64 ff ff   call __getptd (rel32 -> FA 0x4d9150)
//   83 c0 54         add eax,0x54
//   c3               ret
// i.e. return _getptd()+0x54 — _ptd field accessor. Pure CL C — EXACT fit
// (code 0x9, no pad), byte-verify PASS, no tail-accept. No map needed.
extern char *_getptd(void);
char *w24b_chunke2ce0(void) { return _getptd() + 0x54; }
