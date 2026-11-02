// @GRSetLightSource@4 @ rva 0xc9be4 (32 B) — 3 word loads via mov ax,[ecx+2k]
// and a3-moffs word stores into _worldLightSource[0,2,4]; 8bc0 pad.
extern unsigned short w27a_wls0;   /* _worldLightSource */
extern unsigned short w27a_wls1;   /* _worldLightSource+0x2 */
extern unsigned short w27a_wls2;   /* _worldLightSource+0x4 */
void __fastcall GRLightSetQ(unsigned short *src)
{
    w27a_wls0 = src[0];
    w27a_wls1 = src[1];
    w27a_wls2 = src[2];
}