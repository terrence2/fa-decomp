// @G_SPolygonFlip@8 @ rva 616032 (0x96660, 32 B) — patch-hybrid.  The
//   plain-C body (sa=a declared FIRST; both calls on the parked copies)
//   reproduces the frame but CL's 2-arg fastcall park is mirrored vs FA
//   and decl order does NOT steer it (v2 vs v3 byte-identical): CL parks
//   edx->edi / ecx->esi (`8b fa`/`8b f1`) and reloads `8b d7`/`8b ce`,
//   FA parks edx->esi / ecx->edi (`8b f2`/`8b f9`) and reloads
//   `8b d6`/`8b cf` — 4 x 1-B modrm fixes.  FA also carries a 9-B pad
//   tail (8b ff mov edi,edi + 8d a4 24 00 00 00 00) CL never
//   emits (CL bare 5f 5e c3): the 3-B span at offset 20 is expanded to
//   FA's 12-B 5f 5e c3 8b ff 8d a4 24 00 00 00 00.
//   Probe build/survey/probes/p_w23_SPolyFlip_final.obj EXACT (w23_r5.json;
//   ladder w23_G_SPolygonFlip_v1, w23_SPolygonFlip_v2, w23_SPolyFlip_v3
//   + _v3p; park-order lever CONFIRMED NOT steerable by decl order).
//   Maps (swap.json verbatim): [].
//   Patches: "3,1,f2", "5,1,f9", "12,1,d6", "14,1,cf",
//            "20,3,5f5ec38bff8da42400000000".
extern void __fastcall G_Flip(long a, long b);
extern void __fastcall G_SPolygon(long a, long b);

void __fastcall G_SPolygonFlip_q(long a, long b)
{
    long sa = a, sb = b;
    G_Flip(sa, sb);
    G_SPolygon(sa, sb);
}