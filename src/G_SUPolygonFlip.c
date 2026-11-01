// @G_SUPolygonFlip@8 @ rva 0x96680 — push esi / push edi / mov edi,edx /
//   mov esi,ecx / call @G_Flip@8 / mov edx,edi / mov ecx,esi / call
//   @G_SUPolygon@8+0x1000 (interior entry 0xc4b80) / pop edi / pop esi / ret. Unlike _G_SPolygonFlip this
//   pairing IS the pure-C codegen (probe d22 exact): CL writes both
//   fastcall arg spills in the order edi=edx, esi=ecx.
extern void __fastcall G_Flip(int a, int b);
extern void __fastcall G_SUPolygon2(int a, int b);

void __fastcall G_SUPolygonFlip_q(int a, int b)
{
    G_Flip(a, b);
    G_SUPolygon2(a, b);
}
