/* rva 0x78ee0 (64 B, __cdecl): LZW explode read callback.
 * Copies *lenP bytes from the packet-tick read cursor (the pointer valued
 * in field ?packetTicks@@3PAJA+0x518) into dst, advances that cursor by
 * the length, and returns the length. FA's shape: len reloaded from lenP
 * for the memcpy count and again for the return (the rep loops trash
 * eflags only, the reload is CL 4.2's own expansion choice); cursor load
 * is a moffs 8b 35 at +0x8, reload/advance via 8b 0d/+0x24 and store
 * 89 0d/+0x2e - all three dwords are DIR32 sites on +0x518.
 */
#include <string.h>
extern char *w44e_ptCurR;   /* ?packetTicks@@3PAJA+0x518 */

long __cdecl w44e_lzwRead(long *dst, long *lenP)
{
    memcpy(dst, w44e_ptCurR, (unsigned)*lenP);
    w44e_ptCurR = (char *)w44e_ptCurR + *lenP;
    return *lenP;
}