/* Transplant husk (whole-body patch) for _G_UVline@12, rva 613264 (0x95b90), 160 B.
 * FA semantics (dis.py 0x95b90): stdcall(a, c0, c1) — vertical line fill:
 *   cb = _cb; x = *(int*)(cb+2) * c0 + *(int*)(cb+0xa) + a;   // imul ecx,edx; add ebx
 *   edi = x;                                                  // lea edi,[ecx+eax]
 *   if (!_cFillType && c1 >= c0) {                            // firstDraw-ish fill
 *     for (n = c1 - c0 + 1; n; n--) { *edi = _cColor;
 *       edi += *(int*)(cb+2); }                               // _cb RELOADED per iter
 *   }
 *   if (_cFillType == 1 && c1 >= c0) {
 *     for (n = c1 - c0 + 1; n; n--) { *edi = cRemapTable[*edi];
 *       edi += *(int*)(cb+2); } }                             // _cb reloaded per iter
 *   memset((void*)&_lineStats[c0], 0xff, c1-c0+1);            // rep stosd/stosb, lea edi,[edx+0x50bb40]
 *   ret 0xc
 * CL's per-iteration global reload + 0x50bb40 moffs fill don't reproduce; body fully
 * patched over husk.
 */
void __stdcall G_UVline(long a, long b, long c) { (void)a; }