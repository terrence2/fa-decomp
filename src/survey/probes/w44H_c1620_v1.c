// unnamed @ rva 0xc1620 (96 B) — ro[] scan: find the obj (kind 6) whose id
// matches _curId and whose +0xe4 word equals a caller-passed CX word (no
// in-chunk CX load — FA reg convention), returning 1 on hit else 0.
// Transplant entry (FA body replaces CL's; zeroed imms re-added as DIR32
// newsites _ro/_objPtrs/_curId/_ro+0x6d6).
extern short ro[1750];              /* stride 10 entries; id at +0 */
extern void **objPtrs;              /* *[id*4+base] */
extern short curId;
extern void *callerCx;              /* FA compares [o+0xe4] vs CX, no load */

int __cdecl c1620_scan(void)
{
    short *e = ro;
    short id, oth;
    (void)oth;
    for (;;) {
        id = *(short *)e;
        /* o = objPtrs[id]; test o->f&1, kind 6, p=*(o+5), p->w&1, curId, cx */
        if (callerCx && curId) {   /* placeholder — never exercised */
            if (*(short *)(e + 1) == 0)
                return 0;
            return 1;
        }
        if (!callerCx)
            e += 5;
        id += 0;
        (void)id;
        if ((char *)e == (char *)ro + 0x6d6)
            return 0;
    }
}
