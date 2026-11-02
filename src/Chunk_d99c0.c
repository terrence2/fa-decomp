// w24b_chunkd99c0 @ rva 0xd99c0 (891328, unnamed gap, 9 B) — FA bytes:
//   e8 8b f7 ff ff   call __getptd (rel32 -> FA 0x4d9150)
//   83 c0 0c         add eax,0xc
//   c3               ret
// i.e. return _getptd()+12 — _ptd field accessor. Pure CL C — EXACT fit
// (code 0x9, no pad), byte-verify PASS, no tail-accept. C-level `_getptd`
// decorates to obj `__getptd` = FA chunk name; no map needed. char* + 12
// gives the literal add-eax form CL uses for raw pointer arithmetic.
extern char *_getptd(void);
char *w24b_chunkd99c0(void) { return _getptd() + 12; }
