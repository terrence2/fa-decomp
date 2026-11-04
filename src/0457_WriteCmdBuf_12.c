// 0x62e10 @WriteCmdBuf@12 (80 B) — v1
// fastcall: (char b @ecx, char *src @edx, unsigned short n @stack).
// Writes b at *ccp, bumps ccp, then memcpy(ccp, src, n) (inline rep
// movsd/movsb) and ccp += n. The FA chunk carries a stray 90 at off 7
// (between push edi and the store) — expect a 1-byte patch insert.
extern void *memcpy(void *, const void *, unsigned);
extern char *w29a_ccp;   /* ?correctChainPlacement@@3DA+0x20 */

void __fastcall w29a_WriteCmdBuf(char b, char *src, unsigned short n)
{
    *(char *)w29a_ccp = b;
    w29a_ccp = (char *)w29a_ccp + 1;
    if (n != 0)
    {
        memcpy(w29a_ccp, src, (unsigned)n);
        w29a_ccp = (char *)w29a_ccp + n;
    }
}