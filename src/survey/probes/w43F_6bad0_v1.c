/* w43F 0x6bad0 (112 B, fastcall 1 reg arg ecx, long return): 16-bit-period
 * wrap arithmetic.  FA: push esi; two big-excursion arms with REAL unsigned
 * div by 0xfff0 (div esi) and (q<<12 - q)<<4 multipliers; two small-clamp
 * ifs (cmp 0xffff8008 / cmp 0x7ff8, +-= 0xfff0); mov eax,ecx; pop esi; ret.
 * No abs sites; 8bff+8da424 tail (census).
 */
long __fastcall w43F_6bad0(long key)
{
    unsigned long q;
    if (key < (long)0xffff0010) {
        q = (0xffffffffu - (unsigned long)key) / 0xfff0u;
        key += (long)(((q << 12) - q) << 4);
    }
    if (key > (long)0xfff0) {
        q = ((unsigned long)key - 1u) / 0xfff0u;
        key -= (long)(((q << 12) - q) << 4);
    }
    if (key < (long)0xffff8008) key += (long)0xfff0;
    if (key > (long)0x7ff8) key -= (long)0xfff0;
    return key;
}