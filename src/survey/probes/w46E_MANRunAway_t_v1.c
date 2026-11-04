/* Transplant husk (whole-body patch) for @MANRunAway@4, rva 507824 (0x7bfb0), 160 B.
 * FA semantics (dis.py 0x7bfb0): thiscall (ecx = spawn count n), esp frame 3 dwords:
 *   for (i = n; i > 0; i--) {                  // esi = i-1 down-count, edi = 0
 *     long pt[3];
 *     pt[0] = *(long*)0x508749                  // _curThing+0x11 (interior dword load 8b0d)
 *           + (long)(short)Rand(4000)*256 - 2000*256;   // movsx ax; sub 0x7d0; shl 8; add ecx
 *     pt[1] = 0;                                // store edi (zeroed pre-loop) at [esp+0xc]
 *     pt[2] = *(long*)0x508751                  // _curThing+0x19
 *           + (long)(short)Rand(4000)*256 - 2000*256;
 *     w = (short)Rand(60) + 60;                 // rand3: movsx; add 0x3c
 *     MANAdd(_thisComputer, (void(*)(void))0x4f4124,       // ?stallWarnSnd@@3FA+0x34
 *            *(char*)0x508741,                       // _curThing+0x9 byte, pushed as edx
 *            (void*)0x508749,                        // &_curThing+0x11 addr push
 *            pt, w);
 *   }
 * CL C cannot spell thiscall-from-C single-arg entry (used fastcall: same @4 ABI) with
 * FA's exact reg schedule; husk carries only the mangled public — body fully patched.
 */
void __fastcall MANRunAway(long a) { (void)a; }