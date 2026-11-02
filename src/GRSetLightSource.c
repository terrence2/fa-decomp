// @GRSetLightSource@4 — src struct has 2-byte pads: fields at +0,+4,+8
// (FA loads 66 8b 41 04 / +8 with ecx kept as base).
extern unsigned short w27a_wls0;  /* _worldLightSource */
extern unsigned short w27a_wls1;  /* _worldLightSource+0x2 */
extern unsigned short w27a_wls2;  /* _worldLightSource+0x4 */
struct w27a_lsrc { unsigned short r, p1, g, p2, b; };
void __fastcall w27a_grls_q(struct w27a_lsrc *src)
{
    w27a_wls0 = src->r;
    w27a_wls1 = src->g;
    w27a_wls2 = src->b;
}
