/* APGetPark - FA rva 0xb9770 (759664) - EXACT probe verdict, tier1_a_r3.json entry 'APGetPark_v5'
 * Form: patch-hybrid
 * Levers: 11-byte region reorder patch (cmp dx,ax before lea)
 * Maps: _curThing231=_curThing+0x231, __curId=_curId
 * patch 0x20: 11 B reorder: 66 3b d0 7e 1d 8d b1 11 01 00 00
 * Probes: v1-v5
 */
extern char *curThing231;
extern unsigned short _curId;

int __stdcall APGetPark(void)
{
    int i;
    short cnt;
    unsigned short *p;
    if (!curThing231)
        return -1;
    i = 0;
    cnt = *(short *)((char *)curThing231 + 0xe0);
    p = (unsigned short *)((char *)curThing231 + 0x111);
    if (cnt > i) {
        do {
            if (*p == _curId)
                return i;
            ++p;
            ++i;
        } while (cnt > i);
    }
    return -1;
}
