/* GetFakeKey - FA rva 0x11cb0 (72880) - EXACT probe verdict, tier1_a_r2.json entry 'GetFakeKey_v6'
 * Form: plain C
 * Levers: zero-path-at-end spelling
 * Maps: _adCount=?adCount@@3EA
 * Probes: v5,v6
 */
extern char waitCounter[];
extern char adCount[];

unsigned short __stdcall GetFakeKey(void)
{
    short k = *(unsigned short *)(waitCounter + 4);
    unsigned short r;
    if (k) {
        --k;
        *(unsigned short *)(waitCounter + 4) = k;
        r = *(unsigned short *)(adCount + 8 + k * 2);
        return r;
    }
    return 0;
}
