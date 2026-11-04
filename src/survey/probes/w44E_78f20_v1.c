/* rva 0x78f20 (64 B, __cdecl): LZW explode write callback - the mirror of
 * the read callback. Copies *lenP bytes from src into the packet-tick
 * write cursor (pointer valued in field ?packetTicks@@3PAJA+0x51c) and
 * advances it: cursor load is moffs 8b 3d at +0xe, reload/advance via
 * 8b 0d/+0x24 (add), store 89 0d/+0x2e, all DIR32 sites on +0x51c.
 * FA's return value is the lenP POINTER itself (eax holds [esp+8] from
 * entry and is never rewritten: 8b 44 24 08 at entry, c3 at the end) -
 * callers only read the low byte, so the transplant keeps FA's actual
 * register state. len is reloaded from lenP for the advance (+0x20
 * mov edx,[eax]) after the rep loops.
 */
#include <string.h>
extern char *w44e_ptCurW;   /* ?packetTicks@@3PAJA+0x51c */

long __cdecl w44e_lzwWrite(long *src, long *lenP)
{
    memcpy(w44e_ptCurW, src, (unsigned)*lenP);
    w44e_ptCurW = (char *)w44e_ptCurW + *lenP;
    return (long)lenP;
}