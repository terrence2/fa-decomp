/* ?code@@YAJJJ@Z @ 0x96c20 (144 B): snow/eclipse zone classifier.
 * long code(long a, long b)     [cdecl C++]
 *   if (a < *(long*)(_snowLow+8))  { if (b > *(long*)(_snowLow+4))
 *                                       return 9;
 *                                    return (b < *(long*)(_eclipRight+4))
 *                                       ? 3 : 1; }
 *   else if (a <= *(long*)(_snowLow+12)) {
 *       if (b > *(long*)(_snowLow+4)) return 8;
 *       return (b >= *(long*)(_eclipRight+4)) ? 0 : 2; }
 *   if (b > *(long*)(_snowLow+4)) return 12;
 *   return (b < *(long*)(_eclipRight+4)) ? 6 : 4;
 * CL scheduling diverges from FA throughout (a1-first cmp / operand-order
 * canonicalization wall — wave-19/28 classes; CL colors (a,sym)=(eax,ecx),
 * FA (ecx,eax); cmp operand order canonicalized) -> whole-body transplant of
 * the 130 FA code bytes with 7 DIR32 newsites:
 *   0x05:_snowLow+0x8  0x12:_snowLow+0x4  0x22:_eclipRight+0x4
 *   0x36:_snowLow+0xc  0x41:_snowLow+0x4  0x53:_eclipRight+0x4
 *   0x74:_eclipRight+0x4
 * FA dword values on disk verified = symVA+delta for all 7 sites.
 * Donor husk body below is only there to yield a compilable CL obj; its
 * bytes are fully replaced by the transplant patch.
 */
long code(long a, long b)
{
    return a > b;
}