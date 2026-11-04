// @G_SetScaleMax@8 @ rva 0x96540 — mov [_scaleMaxW],ecx / mov
//   [_scaleMaxH],edx / ret: fastcall (w,h) stores, identities on the two
//   FA data symbols.
extern long scaleMaxW;
extern long scaleMaxH;

void __fastcall G_SetScaleMax_q(long w, long h)
{
    scaleMaxW = w;
    scaleMaxH = h;
}
