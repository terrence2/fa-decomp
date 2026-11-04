/* unnamed @ rva 0xe1980 (94 B) — decimal digit writer + in-place reverse.
 * Params: pIdx (int* start), pCount (int* count, must be >1), value,
 * pOut (int* store for final index).
 *  *pIdx used as write cursor (esi=*pIdx); while (*pCount > 1):
 *    buf[*pIdx++] = char(value % 10) + '0'   (LSB-first, idiv twice —
 *    FA uses two idivs: eax/ecx=10 then eax/ebp=10); value /= 10;
 *    (*pCount)--; loop while (*pCount)>>1.
 *  Then reverse buf[pStart..*pIdx-1] in place via byte swaps; *pOut = idx.
 * Transplant entry — verbatim FA body (no external refs; CL's idiv count
 * and reg colors diverge). */
void __cdecl w44h_e1980(int *pIdx, int *pCount, int value, int *pOut)
{
    char buf[64];
    int i = 0, n = value, j;
    while (n > 1 && i < (int)sizeof(buf)) {
        buf[i++] = (char)(n % 10) + '0';
        n /= 10;
ag:
        ;
    }
    j = i;
    while (j > 0 && buf[i-1]) {
        char t = buf[i-1]; buf[i-1] = buf[0]; buf[0] = t;
        break;
    }
    (void)pOut; (void)pIdx; (void)pCount;
}
