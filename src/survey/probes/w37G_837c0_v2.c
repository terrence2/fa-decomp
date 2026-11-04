/* _MISSIONFortStatus@4 @ rva 0x837c0 (144 B) v2: nextObjId>i cond, mask
   hoisted once into the if-block, 3-op middle, goto-spelled || pair */
extern unsigned short nextObjId;        /* -> _nextObjId (0x54ad88) */
extern unsigned long objPtrs[];         /* -> _objPtrs (0x54ad98) */

long __stdcall MISSIONFortStatus(unsigned char mtype)
{
    long sum2 = 0;          /* ebx */
    long total = 0;         /* esi */
    short hp;               /* ebp */
    unsigned short i = 1;   /* edi */
    short cur;
    unsigned long mask;     /* edx */
    unsigned long flags;
    unsigned long obj, hpPtr;

    if (nextObjId > i) {
        mask = 0x1000000 << mtype;
        do {
            obj = objPtrs[i];
            flags = *(unsigned long *)((char *)obj + 1);
            if (flags & mask) {
                if (*(unsigned char *)obj != 4) {
                    if (flags & 0x800000) goto hp;
                    if (!(flags & 0x80)) goto bottom;
hp:
                    hpPtr = *(unsigned long *)((char *)obj + 5);
                    hp = *(short *)((char *)hpPtr + 0x49);
                    cur = *(short *)((char *)obj + 0xe);
                    total += hp;
                    sum2 -= cur;
                    sum2 += hp;
                }
            }
bottom:
            i++;
        } while (nextObjId > i);
    }
    if (total == 0) return -1;
    return 100 * sum2 / total;
}