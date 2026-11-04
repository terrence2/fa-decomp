/* _MISSIONFortDestroyedByFort@4 @ rva 0x83730 (144 B) v2: FA loop cond nextObjId > i */
extern unsigned short nextObjId;        /* -> _nextObjId (0x54ad88) */
extern unsigned long objPtrs[];         /* -> _objPtrs (0x54ad98) */
extern char __fastcall Alive(unsigned long obj);   /* -> @Alive@4 */

char __stdcall MISSIONFortDestroyedByFort(unsigned long mask)
{
    long count = 0;         /* ebx (FA) */
    unsigned short i = 1;   /* edi */
    long destroyed = 0;     /* ebp */
    unsigned long flags;
    unsigned long obj;

    if (nextObjId > i) {
        do {
            obj = objPtrs[i];
            flags = *(unsigned long *)((char *)obj + 1);
            if (flags & mask) {
                if (*(unsigned char *)obj != 4) {
                    if (flags & 0x800000) {
                        count++;
                        if (flags & 1) { if (Alive(obj) == 0) destroyed++; }
                        else destroyed++;
                    } else if (flags & 0x80) {
                        count++;
                        if (flags & 1) { if (Alive(obj) == 0) destroyed++; }
                        else destroyed++;
                    }
                }
            }
            i++;
        } while (nextObjId > i);
    }
    if (destroyed == count && count != 0) return 1;
    return 0;
}