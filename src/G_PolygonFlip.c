// @G_PolygonFlip@8 @ rva 615904 (0x965e0, 64 B) — plain C.  Decisive levers:
//   park locals sa=a/sb=b declared BEFORE the guards (FA: mov esi,ecx FIRST,
//   mov edi,edx second; both calls take (a,b) in correct (ecx,edx) order —
//   dis.py 8b d6/8b cf confirms), guards as separate ifs with FloatFlatFlip on
//   the original ecx/edx.  Wave-3 char-vs-int and GSPolyFlip misparse taught:
//   FA parks (esi,edi) = (ecx,edx) in decl order.
//   Probe build/survey/probes/p_w23_GPolyFlip_v2.obj EXACT (w23_r2.json).
//   Maps (swap.json verbatim): _gFloatFlatFlip=@G_FloatFlatFlip@8,
//   _gFlip=@G_Flip@8, _gPolygon=@G_Polygon@8.
extern char cFillType;
extern long effects;
extern void __fastcall G_FloatFlatFlip(long a, long b);
extern void __fastcall G_Flip(long a, long b);
extern void __fastcall G_Polygon(long a, long b);

void __fastcall G_PolygonFlip_q(long a, long b)
{
    long sa = a, sb = b;
    if (cFillType) {
        if (effects & 0x10000) {
            G_FloatFlatFlip(a, b);
            return;
        }
    }
    G_Flip(sa, sb);
    G_Polygon(sa, sb);
}