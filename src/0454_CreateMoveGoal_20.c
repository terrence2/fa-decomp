/* Transplant husk (whole-body patch) for _CreateMoveGoal@20, rva 404656 (0x62cb0), 160 B.
 * FA semantics (dis.py 0x62cb0): stdcall(a,b,c,d,e), esp frame:
 *   switch (e-4) {            // lea eax,[b-4]; cmp 4; ja; jmp [[eax+table@+0x88]] 5 dwords
 *     0: t = (short)(d>>16); break;                      // sar 0x10 + movsx
 *     1: t = d>>8 (arith); break;                        // sar 0x8
 *     2: t = d*4 unless d==0x7fff; e=7; break;           // cmp 0x7fff je; shl 2
 *     3: t = d; break;
 *   }
 *   common: if (esi == (void*)curThing+0x38)            // cmp esi,0x508770 (_curThing+0x38)
 *             t = (unsigned short)$FA$_t_462d50();      // fastcall (arg via ecx=esi);
 *   dst: B[a+c+0x18] = dl|bl; W[a*2+0x1a] = (u16)t;     // 0a d3 or; 88 54 06 18; 66 89 4c 46 1a
 *   ret 0x14
 * CL's switch/table + thiscall-ish reg flow don't match; body fully patched over husk.
 */
void __stdcall CreateMoveGoal(long a, long b, long c, long d, long e)
{ (void)a; }