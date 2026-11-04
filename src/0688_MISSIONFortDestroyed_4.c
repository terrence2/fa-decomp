// _MISSIONFortDestroyed@4 v3 — redecode with the mask LIVE:
//   test eax,esi = `a & mask` (85 f0, not test eax,eax!); the a9 imm is
//   0x00800000; exit is `if (cnt == nalive && cnt != 0) return 1; return 0;`
//   (FA: cmp ebp,ebx / jne ret0; test ebx,ebx / je ret0; mov al,1).
extern unsigned short w43b_next;   /* _w43b_next=_nextObjId */
extern long w43b_objP[];           /* _w43b_objP=_objPtrs */
extern long w43b_pforts[];         /* _w43b_pforts=_playerForts */
extern char __fastcall w43b_Alive(char *o);  /* @w43b_Alive@4=@Alive@4 */

char __stdcall w43b_fortdead3(long val)
{
    long cnt;
    long nalive;
    long o;
    unsigned long a;
    unsigned long mask;
    unsigned char fl;
    unsigned short i;

    i = 1;
    cnt = 0;
    nalive = 0;
    if (*(unsigned short *)&w43b_next > i) {
        mask = 0x1000000 << (w43b_pforts[val] & 0xff);
        do {
            o = w43b_objP[i];
            a = *(unsigned long *)(o + 1);
            if (a & mask) {
                fl = *(unsigned char *)o;
                if (fl != 4) {
                    if (a & 0x800000) {
                        cnt++;
                        if (a & 1) {
                            if (w43b_Alive((char *)o) == 0)
                                nalive++;
                        } else
                            nalive++;
                    } else if (a & 0x80) {
                        cnt++;
                        if (a & 1) {
                            if (w43b_Alive((char *)o) == 0)
                                nalive++;
                        } else
                            nalive++;
                    }
                }
            }
            i++;
        } while (*(unsigned short *)&w43b_next > i);
    }
    if (cnt == nalive && cnt != 0)
        return 1;
    return 0;
}