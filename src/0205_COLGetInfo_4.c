// _COLGetInfo@4 @ rva 0x2dbf0 (64 B) — FA asm (plain-C reachable):
//   p = *(char**)((char*)id + 0xf) / if !p return &mcFlyAll+0x114c /
//   p += 0xe / if *(short*)p != 0xf2 return &mcFlyAll+0x114c /
//   p += 2 / return p + 2 + *(unsigned short*)p
// Walks a car-list object to its info record. Plain C matched CL exactly
// (probe b19b_cgi_v1). Map: _mcFlyAll=?mcFlyAll@@3DA (c++-mangled FA
// global; +0x114c baked via addend map).
extern char mcFlyAll[];

long __stdcall COLGetInfo(long id)
{
    char *p;

    p = *(char **)((char *)id + 0xf);
    if (p == 0)
        return (long)(mcFlyAll + 0x114c);
    p += 0xe;
    if (*(short *)p != 0xf2)
        return (long)(mcFlyAll + 0x114c);
    p += 2;
    return (long)(p + 2 + *(unsigned short *)p);
}