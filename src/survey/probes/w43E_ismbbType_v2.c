/* FA 0xdb810 _ismbbType (58 B) v2: 3-arg (c, type, mask); mask tested in memory */
extern unsigned char mbyte1Data[];  /* _mbctype+0x1 (per-byte flag table) */
extern unsigned short ctyp2Data[];  /* _ctype+0x2 word table */

int __cdecl w43E_ismbbTypeQ(unsigned long c, unsigned long type, unsigned long mask)
{
    if (mask & (unsigned)mbyte1Data[(unsigned char)c])
        return 1;
    if (type == 0)
        return 0;
    return (ctyp2Data[(unsigned char)c] & type) != 0;
}