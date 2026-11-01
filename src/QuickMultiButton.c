// @QuickMultiButton@8 @ rva 0x2e1b0 — same two [ecx*4+disp32],edx stores into
//   _specials at +0xd08 and +0xc08 (probe v11 shape).
extern long qmbA_x[];
extern long qmbB_x[];

void __fastcall QuickMultiButton(int i, int v)
{
    qmbA_x[i] = v;
    qmbB_x[i] = v;
}
