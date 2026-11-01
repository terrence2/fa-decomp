// ?spxfactory@@YAXPAUNET_PROTOCOL@@PADH@Z @ rva 0x95400 (16 B) — empty-body
//   stub sibling of spxinit2 (wave-15/src/spxinit2.c: same UNET_PROTOCOL
//   net-protocol family): FA asm is a bare c3 + 15 B leal/leal census pad.
//   Empty cdecl body with unused params is exact (probe b19c_spx; the
//   wave-17 empty-body exports rule: noIO/printPoly/SetTOD/SetVESATop).
void __cdecl spxfactory(void *proto, char *name, int flag)
{
}