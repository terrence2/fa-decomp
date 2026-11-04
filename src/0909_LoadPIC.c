// _LoadPIC @ rva 0xa3cf0 (96 B; code 95 B + 1-B 90 census tail).  cdecl
// (void *p1, unsigned long p2).  V2b: 16-B local rbuf[4] (&rbuf[0] as the
// handle buffer), arg2 = low word of the p2 slot read via ushort-alias
// (FA: 66 8b 44 24 24 / 0c 90), no extra locals (FA saves only esi).
extern long __fastcall w43H_rmfind(long item);      /* =@w43H_rmfind@4=@RMFind@4 */
extern void __stdcall w43H_rmct(void *item, char *str, void *loc); /* =_w43H_rmct@12=_RMChangeType@12 */
extern long __stdcall w43H_glb(void *loc, unsigned long mode, long brs,
    long av1, long av2);   /* =_w43H_glb@20=_G_LoadBitmap@20 */
extern void __stdcall w43H_rml(long item, long n, long res); /* =_w43H_rml@12=_RMLocate@12 */
extern short w43H_avr18;    /* =?averageTest@@3_JA+0x18 */
extern short w43H_avr1c;    /* =?averageTest@@3_JA+0x1c */
extern short w43H_brs;      /* =_brsColorProcess */
extern char w43H_lit2[];    /* =_IID_IDirectDrawClipper+0x22a8 */

void __cdecl w43H_LoadPIC5(void *p1, unsigned long p2)
{
    unsigned long rbuf[4];
    long r;
    if (w43H_rmfind((long)p1) == 0) {
        w43H_rmct(p1, w43H_lit2, &rbuf[0]);
        r = w43H_glb(&rbuf[0], (unsigned long)*(unsigned short *)&p2 | 0x90,
            w43H_brs, w43H_avr1c, w43H_avr18);
        if (r)
            w43H_rml((long)p1, 3, r);
    }
}