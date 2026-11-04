/* _HARDHasInternalBay@4 0x53110 v2: no o1/o2 init stores; signed loop tail. */
extern unsigned char curThingType[];    /* _curThingType */
extern void *__stdcall HARDPtrs(long id, void **o1, void **o2);

unsigned char __stdcall w44acHardBay(long id)
{
    unsigned char r = 0;
    void *o1;
    void *o2;
    void *t;
    long i;

    if (id != -1) {
        t = HARDPtrs(id, &o1, &o2);
        if (t) {
            if (*(long *)o1 != 0) {
                if (*(unsigned char *)t == 7) {
                    if (*(unsigned char *)((char *)o2 + 0x17) == 3)
                        r = 1;
                }
            }
        }
        return r;
    }
    i = 0;
    if (curThingType[0xb5]) {
        do {
            t = HARDPtrs(i, &o1, &o2);
            if (t) {
                if (*(long *)o1 != 0) {
                    if (*(unsigned char *)t == 7) {
                        if (*(unsigned char *)((char *)o2 + 0x17) == 3)
                            r = 1;
                    }
                }
            }
            i++;
        } while (curThingType[0xb5] > i);
    }
    return r;
}