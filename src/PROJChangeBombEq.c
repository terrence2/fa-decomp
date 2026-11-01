// _PROJChangeBombEq@8 @ rva 0xc03d0 (32 B) — copy the 3 dword bomb-eq payload
//   src[0..2] into dst+0xc..0x14.  C int-array form gave 89 42 0c folded
//   addressing; only the struct member copy (dst->eq = src->first) yields FA's
//   add edx,0xc / interleave with ebx+ecx rotate and the mid-body 5b pop.
struct EQ { int x, y, z; };
struct T  { struct EQ first; struct EQ eq; };

void __stdcall PROJChangeBombEq(struct T *dst, struct T *src)
{
    dst->eq = src->first;
}