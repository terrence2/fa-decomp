// w40G_SeqRect_v2 — corrected FA reg plan: esi=p1 (b), edi=p3 (d) ->
// w = d-b+1, ebx=p4 (e), eax=p2 (c) -> h = e-c+1; loop G_UHline(b, b+w-1,
// c+k) with k in ebp; memset(lineStats + c, -1, h). "b + w - 1" spelled to
// reproduce FA's lea ecx,[esi+edi*1-1] x2 arg.
extern void __stdcall G_UHline(long x1, long x2, long y);
extern char lineStats[];

void __stdcall SeqRect(long b, long c, long d, long e)
{
    long w, h, k;
    w = d - b + 1;
    h = e - c + 1;
    k = 0;
    while (k < h) {
        G_UHline(b, b + w - 1, c + k);
        k++;
    }
    memset(lineStats + c, 0xff, h);
}