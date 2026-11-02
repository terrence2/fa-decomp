/* v3: v2 shape + volatile flags to force FA's per-branch 8b 0d loads. */
extern void __stdcall w28a_pushCur(void *o);       /* =_PushCurObj@4 */
extern long __fastcall w28a_findJammer(unsigned char t);  /* =@HARDFindJammer@4 */
extern void __stdcall w28a_popCur(void);           /* =_PopCurObj@0 */
extern void *__stdcall w28a_hardPtrs(long idx, int a, int b);  /* =_HARDPtrs@12 */
extern volatile unsigned long w28a_flags;     /* =_curThing+0xde */

void *__fastcall w28a_HARDFindECMForObj(unsigned char thing, void *obj)
{
    void *res;
    long j;
    w28a_pushCur(obj);
    j = w28a_findJammer(thing);
    if (j != -1) {
        if (thing == 3) {
            if ((w28a_flags & 0x10) == 0) goto bail;
        } else if (thing == 2) {
            if ((w28a_flags & 0x20) == 0) goto bail;
        }
        res = w28a_hardPtrs(j, 0, 0);
        goto out;
    }
bail:
    res = 0;
out:
    w28a_popCur();
    return res;
}
