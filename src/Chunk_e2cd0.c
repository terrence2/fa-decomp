// w24b_chunke2cd0 @ rva 0xe2cd0 (928976, unnamed gap, 9 B) — FA bytes:
//   e8 7b 64 ff ff   call __getptd (rel32 -> FA 0x4d9150)
//   83 c0 58         add eax,0x58
//   c3               ret
// i.e. return _getptd()+0x58 — _ptd field accessor. Pure CL C — EXACT fit
// (code 0x9, no pad), byte-verify PASS, no tail-accept. No map needed
// (C `_getptd` -> obj `__getptd` = FA chunk name).
extern char *_getptd(void);
char *w24b_chunke2cd0(void) { return _getptd() + 0x58; }
