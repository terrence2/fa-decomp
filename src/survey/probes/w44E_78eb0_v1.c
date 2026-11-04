/* rva 0x78eb0 (48 B, __cdecl, 3 params): LZW stream bootstrap.
 * Installs the read/write cursors for the packet-tick LZW decompress by
 * writing arg1 into the read cursor (field ?packetTicks@@3PAJA+0x518) and
 * arg3 into the write cursor (+0x51c), then calls _explode (unnamed stub,
 * rva 0x1000) with the fixed decoder callbacks at rva 0x478ee0 (reader)
 * and 0x478f20 (writer) against _lzwBuff:
 *   _explode(0x478ee0, 0x478f20, _lzwBuff, 0).
 * arg2 ([esp+8]) is dead - FA never reads it.
 * FA interleaves the two cursor stores inside the push sequence
 * (push 0 / store+0x518 / push _lzwBuff / store+0x51c / push wfn /
 * push rfn / call) - kept verbatim by the transplant.
 */
extern char lzwBuff;                                  /* _lzwBuff */
extern char *w44e_ptCurR;   /* ?packetTicks@@3PAJA+0x518 */
extern char *w44e_ptCurW;   /* ?packetTicks@@3PAJA+0x51c */
extern void __cdecl explode(char *rfn, char *wfn, char *buf, long mode);
extern char *__cdecl FA_t_478ee0(long *dst, long *lenP);
extern long __cdecl FA_t_478f20(long *src, long *lenP);

void __cdecl w44e_lzwSetup(char *arg1, long *arg2, char *arg3)
{
    w44e_ptCurR = arg1;
    w44e_ptCurW = arg3;
    explode(FA_t_478ee0, FA_t_478f20, &lzwBuff, 0);
}