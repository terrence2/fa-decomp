/* w35G _HARDClearUnloadedHarpoints@0 @ rva 0x52e20 (112 B) v2 — w34E_a86b0 twin.
 * v2 changes vs v1: inner counter `i` declared BEFORE the 16-bit outer `j`
 * (FA register roles: inner=esi, outer=di; v1 got the swap back-to-front);
 * i = 0 hoisted before the count test (FA's xor esi order); inner loop
 * compare is SIGNED (`> i`) against a zero-extended byte so CL emits
 * `cmp eax,esi` + `jg` (v1's unsigned cast emitted `cmp eax,edi` + `ja`).
 * FA 111 B code + 1 B tail (90).
 */
extern volatile unsigned short w35g_no[];    /* =_nextObjId (word) */
extern char curThing;                        /* =_curThing */
extern char curThingType[];                  /* =_curThingType */
extern void __fastcall GetCurObj_q(unsigned short id);   /* =@GetCurObj@4 */
extern void __fastcall PutCurObj_q(void);                /* =@PutCurObj@0 */
extern void *__stdcall HARDPtrs_q(int, void **, void *); /* =_HARDPtrs@12 */

void __stdcall ClearUnloadedHarpoints_q(void)
{
    unsigned long local;
    unsigned long zed;
    long i;
    unsigned short j;
    unsigned long *slot;

    for (j = 1; (unsigned long)w35g_no[0] > (unsigned long)j; j++) {
        zed = 0;
        GetCurObj_q(j);
        if (curThing == 2 || curThing == 4) {
            i = 0;
            if ((unsigned char)curThingType[0xb5] != 0) {
                do {
                    HARDPtrs_q(i, &local, zed);
                    slot = (unsigned long *)local;
                    if (*(unsigned short *)((char *)slot + 4) == (unsigned short)zed)
                        *slot = zed;
                    i++;
                } while ((unsigned char)curThingType[0xb5] > i);
            }
        }
        PutCurObj_q();
    }
}