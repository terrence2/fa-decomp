// @InitRand@4 @ rva 0x557e0 (16 B) — movsx (short)arg / cdq / xor eax,edx /
//   sub eax,edx (= abs) / neg (= -abs) / mov [campaignPlane+0x1c0],eax / ret.
//   The -abs(x<0?-x:x) form makes CL 4.2 emit FA's exact sign-trick idiom.
extern unsigned char campaignPlane[];

void __fastcall InitRand(int a)
{
    long v = -( (short)a < 0 ? -(short)a : (short)a );
    *(long *)((char *)campaignPlane + 0x1c0) = v;
}
