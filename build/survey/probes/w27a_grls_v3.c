// @GRSetLightSource@4 v3 — named short temp keeps all loads in ax -> 66 a3.
extern unsigned short w27a_wls0;  /* _worldLightSource */
extern unsigned short w27a_wls1;  /* _worldLightSource+0x2 */
extern unsigned short w27a_wls2;  /* _worldLightSource+0x4 */
struct w27a_lsrc { unsigned short r, p1, g, p2, b; };
void __fastcall w27a_grls_q(struct w27a_lsrc *src)
{
    unsigned short t;
    t = src->r;
    w27a_wls0 = t;
    t = src->g;
    w27a_wls1 = t;
    t = src->b;
    w27a_wls2 = t;
}
