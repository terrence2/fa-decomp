/* unnamed 0x268d8: obj-scan counter walk. cdecl (ret 8): two out params;
   ushort si index over the _objPtrs table; byte tests on each entry. */
extern unsigned short w44aObjCnt;   /* map: _w44aObjCnt=_nextObjId */
extern unsigned long w44aObjP[];    /* map: _w44aObjP=_objPtrs */

void __cdecl w44acObjScan(long *r1, long *r2)
{
    unsigned short i = 1;
    *r1 = 0;
    *r2 = 0;
    if (w44aObjCnt > i) {
        do {
            unsigned char *o = (unsigned char *)w44aObjP[i];
            if (o[1] & 1) {
                if (o[0x10] & 0x80)
                    ++*r1;
                if (*o == 4)
                    ++*r2;
            }
            i++;
        } while (w44aObjCnt > i);
    }
}