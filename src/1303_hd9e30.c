// w24b_chunkd9e30 @ rva 0xd9e30 (892464, unnamed gap, 11 B) — FA bytes:
//   6a fd            push 0xfffffffd        (-3)
//   e8 d9 fc ff ff   call __setmbcp (rel32 -> FA 0x4d9b10)
//   83 c4 04         add esp,4
//   c3               ret
// i.e. __setmbcp(-3) — MB_CP init shim. Pure CL C — EXACT fit (code 0xb, no
// pad), byte-verify PASS, no tail-accept. CL renders the -3 literal as the
// sign-extended push 6a fd. C-level `_setmbcp` decorates to obj `__setmbcp`
// = FA chunk name; no map needed.
extern void _setmbcp(int n);
void w24b_chunkd9e30(void) { _setmbcp(-3); }
