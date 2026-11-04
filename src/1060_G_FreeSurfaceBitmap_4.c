// @G_FreeSurfaceBitmap@4 @ rva 0xb3f90 (64 B) — FA asm: push esi / a1 [surfaceBitmap]
//   / cmp [ecx+0xa],eax / jne done / mov [surfaceBitmap],0 / a1 [DDsurfaceBitmap]
//   / test eax,eax / je skip / mov ecx,eax / mov esi,eax / call $FA$_t_4779a0 /
//   push esi / call $FA$_t_4d4880 (the 5th sharer of the free-forwarder anchor)
//   / add esp,4 / skip: mov [DDsurfaceBitmap],0 / done: pop esi / ret.
//   Fastcall G_ cleanup (G_PopClipBox family). Plain C: the DD null test on the
//   GLOBAL gives a1+test eax,eax; p's local copy to esi keeps the value alive
//   across the first (fastcall, clobbering) call — mov ecx,eax/mov esi,eax
//   before call 1; free forwarder is cdecl (add esp,4 after).
extern unsigned char *surfaceBitmap_g;   // -> ?surfaceBitmap@@3PAEA
extern void *DDsurfaceBitmap_g;          // -> ?DDsurfaceBitmap@@3PAVCDirDrawSurface@@A
extern void __fastcall gDdsFreeQ(void *p);
extern void gFreeFwdQ(void *p);

void __fastcall G_FreeSurfaceBitmap_q(long o)
{
    void *p;
    if (surfaceBitmap_g == (unsigned char *)*(unsigned long *)(o + 0xa)) {
        surfaceBitmap_g = 0;
        if (DDsurfaceBitmap_g != 0) {
            p = DDsurfaceBitmap_g;
            gDdsFreeQ(p);
            gFreeFwdQ(p);
        }
        DDsurfaceBitmap_g = 0;
    }
}