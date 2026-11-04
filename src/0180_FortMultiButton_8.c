// @FortMultiButton@8 @ rva 0x1f370 — mov [ecx*4+?fortAwacsDamage@@3DA+8],edx
//   / mov [ecx*4+_fortCount+0x80],edx / ret (probe v11: SIB [ecx*4+disp] in
//   both stores; disp rel addends carried by maps — identity i*4 form).
extern long fortAwacsDamage_x[];
extern long fortCount_x[];

void __fastcall FortMultiButton(int i, int v)
{
    fortAwacsDamage_x[i] = v;
    fortCount_x[i] = v;
}
