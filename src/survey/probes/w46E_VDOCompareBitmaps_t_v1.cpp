// Transplant husk (whole-body patch) for ?VDOCompareBitmaps@@YAKPAUT_HANDLE@@0PAEK@Z,
// rva 706064 (0xac610), 160 B.
// FA semantics (dis.py 0xac610): cdecl(T_HANDLE *a, T_HANDLE *b, unsigned long *dst, unsigned long rows) -> unsigned long diffs:
//   la = MMLockW(a, 1); lb = MMLockW(b, 1);   (fastcall-ish reg pair)
//   W[esi+0xa] vs W[eax+0xa] -> h0/h1; row stride = W[esi+6]; pitch = W[esi+2] (locals -0x14/-0x10/-0xc/-0x4/-0x8)
//   pusha; for each row (ebx = h0): repz cmpsd (ecx = pitch>>2) then byte loop:
//     *dst = (mismatch ? 0xff : 0), dst++;  if (rows==0x3ea) *dst++ = 0 extra separator;
//   popa; return *(unsigned long*)(ebp-8);    // running mismatch count via inc [ebp-8]
// The pusha/popa inline-asm cmpsd loop (wave-18 60/61 trap) is unmapped in CL C;
// body fully patched over husk.
struct T_HANDLE { long a; };
unsigned long VDOCompareBitmaps(struct T_HANDLE *a, struct T_HANDLE *b,
                                unsigned long *p, unsigned long n)
{ (void)a; (void)b; (void)p; (void)n; return 0; }