// _G_ULineFlip@16 @ rva 0x96710 (44 B code + 4 B 8d64 pad) — flips both
// endpoints-x of an unlimited line: G_ULine(x1, m-x2-1, y1, m-y2-1) where
// m = *(int*)((char*)_cb+6).  FA plan: a1 eax=_cb, edx=[eax+6]; args
// computed d-first (mov eax,[esp+0x10]) then c; dec each; push args
// right-to-left with the [esp+X] recount after both pushes.
// Plain-C probe (CL right-to-left eval may reproduce the exact interleave).
extern char* cb;                        /* _cb */
extern void __stdcall G_ULine(int a, int b, int c, int d);

void __stdcall G_ULineFlip_q(int a, int b, int c, int d)
{
    long m = *(long*)((char*)cb + 6);
    G_ULine(a, m - b - 1, c, m - d - 1);
}