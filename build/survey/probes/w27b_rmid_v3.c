// 0xa3c00 _RMFreeAllId@4 (80 B) — v3 (inner test as if(idb==low) so the
// mismatch falls through to the step; no continue)
extern char resList27[];       /* map _resList27=?resList@@3PAURES_LIST@@A */
extern void __stdcall RMFreeX(char *rec);  /* map _RMFreeX=_RMFree@4 */

void __stdcall RMFreeAllId27(short id)
{
    unsigned short idu;
    char *rec;
    unsigned long idb;
    unsigned long low;

    *(char *)(resList27 + 0x67ec) = 0;
    idu = (unsigned short)id;
    rec = resList27;
    do {
        if (*(unsigned char *)rec != 0) {
            idb = *(unsigned char *)(rec + 0xd);
            low = (unsigned long)idu;
            if (idb == low)
                RMFreeX(rec);
        }
        rec = rec + 0x13;
    } while ((unsigned long)rec < (unsigned long)(resList27 + 0x67e8));
    *(char *)(resList27 + 0x67ec) = 1;
}
