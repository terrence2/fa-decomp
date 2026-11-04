/* w46D HARDRestoreHumanLoad rva 339936 (0x452fe0) v1 */
extern long w46d_ncnt;              /* map: _w46d_ncnt=_rudder+0x870 */
extern unsigned short w46d_s16t[];  /* map: _w46d_s16t=_rudder+0x298 */
extern unsigned short w46d_cv;      /* map: _w46d_cv=_curId */
extern unsigned char w46d_ctb;      /* map: _w46d_ctb=_curThing */
extern long w46d_dwq[];             /* map: _w46d_dwq=_rudder+0x2a8 */
extern long w46d_ct1fc;             /* map: _w46d_ct1fc=_curThing+0x1fc */
extern unsigned char w46d_b5;       /* map: _w46d_b5=_curThingType+0xb5 */
extern short w46d_u8s[];            /* map: _w46d_u8s=_rudder+0x878 */
extern long w46d_dtb8[];            /* map: _w46d_dtb8=_rudder+0xb8 */
extern char* __fastcall w46d_hrn_q(char*);            /* map: @w46d_hrn_q@4=@HARDResourceName@4 */
extern void __stdcall HARDLoad_q(long, char*, short); /* map: _HARDLoad_q@12=_HARDLoad@12 */
extern void __fastcall HARDUnloadQ2(long, long);      /* map: @HARDUnloadQ2@8=@HARDUnload@8 */

void __stdcall w46d_rhl_q(void)     /* map: _w46d_rhl_q@0=_HARDRestoreHumanLoad@0 */
{
    long cnt, i, j;
    unsigned short* sp;
    short* wp;
    long* dp;
    cnt = w46d_ncnt;
    sp = w46d_s16t;
    i = 0;
    if (cnt > i) {
        do {
            if (*sp == w46d_cv)
                break;
            sp++;
            i++;
        } while (cnt > i);
    }
    if (w46d_ctb == 4)
        w46d_ct1fc = w46d_dwq[i];
    if (w46d_b5) {
        wp = w46d_u8s + 15 * i;
        dp = w46d_dtb8 + 15 * i;
        j = 0;
        do {
            if (*dp != 0 && *wp != 0)
                HARDLoad_q(j, w46d_hrn_q((char*)*dp), (short)*wp);
            else
                HARDUnloadQ2(j, 0);
            wp++;
            dp++;
            j++;
        } while (w46d_b5 > j);
    }
}