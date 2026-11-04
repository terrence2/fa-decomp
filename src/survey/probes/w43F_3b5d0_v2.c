/* w43F 0x3b5d0 v2: Rand declared SHORT-arg fastcall (decorates @4, Abs
 * precedent); second arg = *(unsigned char *)_snowPtr as short param ->
 * CL emits mov cl,[eax]; and ecx,0xffff00ff (zero-extend byte within a
 * short slot, bits 8-15 cleared, 16-31 garbage).  First arg = literal 100.
 */
extern void __fastcall w43F_GSetCol(long c);
extern short __fastcall w43F_Rand(short n);
extern long w43F_snowLow;               /* _snowLow   0x55344c */
extern long w43F_snowHigh;              /* _snowHigh  0x553374 */
extern long w43F_snowPtr;               /* _snowPtr   0x553464 */
extern long w43F_snowRem;               /* _snowRemainder 0x558418 */

void __fastcall w43F_3b5d0(long color, long p)
{
    long hi, lo;
    hi = p + 0x64;
    w43F_GSetCol(color);
    w43F_snowLow = p;
    w43F_snowHigh = hi;
    lo = w43F_Rand(0x64);
    w43F_snowPtr = p + lo;
    w43F_snowRem = w43F_Rand(*(unsigned char *)w43F_snowPtr);
}
