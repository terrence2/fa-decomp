/* Transplant husk (whole-body patch) for _DialogSetValue, rva 554320 (0x87550), 192 B.
 * FA semantics (dis.py 0x87550): cdecl, args [esp+8..+0x18] = (dp, v, a, b, c):
 *   PushShellAlloc();
 *   esi = DialogGetPtr(dp);
 *   t = *(unsigned short*)esi & 0x7fff;        // 66 8b 06 / 25 ff7f
 *   if (t <= 8) switch (t) {                   // jmp [eax*4+table@+0x98], 9 dwords
 *     case 0: W[0xe]=(u16)v; W[0x10]=(u16)a; W[0x12]=(u16)b; W[0x14]=(u16)c; goto common;
 *     case 2: goto common;                     // 0x4875d2
 *     case 3: B[0x16]=(u8)v; goto common;
 *     case 4: W[0x1a]=(u16)v; W[0x1e]=(u16)a; goto common;
 *     case 7: W[0xc]=(u16)v; $FA$_t_487290(esi); $FA$_t_4872c0(esi); goto common;
 *     case 8: B[0x1e]=(u8)v; goto common;
 *     case 1: case 5: case 6: goto skip;       // straight to PopShellAlloc
 *   }
 *   common: if (!_firstDraw) DialogDraw(esi);
 *   skip: PopShellAlloc();
 * CL's switch-table dword ordering/word-field loads don't reproduce FA's; body fully
 * patched over the husk below.
 */
void DialogSetValue(long dp, long v, long a, long b, long c)
{ (void)dp; }