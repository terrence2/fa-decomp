// w26a_779a0 @ rva 0x779a0 (489632, unnamed 16 B orphan) — FA bytes (raw):
//   e9 2b ff ff ff       jmp ?Destroy@CDirDrawSurface@@QAEXXZ (rel32, ext)
//   8d 64 24 00          (4 B pad) + 8d a4 24 00 00 00 00 (7 B pad) =
//                        census "8d642400+8da42400000000" (11 B)
// A 0-arg-void tail-jmp to CDirDrawSurface::Destroy (this in ecx passes
// straight through). Pure C: a void function calling a 0-arg extern.
extern void CDirDrawSurface_Destroy(void);
void w26a_779a0(void)
{
    CDirDrawSurface_Destroy();
}