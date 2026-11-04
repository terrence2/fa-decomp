/* RMShutdown - FA rva 0xa36c0 (669376) - EXACT probe verdict, tier1_a_r3.json entry 'RMShutdown_v3'
 * Form: plain C
 * Levers: __stdcall RMFree callee (FA _RMFree@4; cdecl emitted 83 c4 04)
 * Maps: _resListArr=?resList@@3PAURES_LIST@@A, _resEnd=?resList@@3PAURES_LIST@@A+0x67e8, _RMFree@4=_RMFree@4
 * Probes: v1-v3
 */
extern char resListArr[];
extern char resEnd;
extern void __stdcall RMFree(void *p);
extern void *memset(void *, int, unsigned long);

void RMShutdown(void)
{
    char *p;
    if (resEnd) {
        p = resListArr;
        do {
            if (*p)
                RMFree(p);
            p += 0x13;
        } while (p < &resEnd);
        memset(resListArr, 0, 0x67e8);
        resEnd = 0;
    }
}
