/* CPSetSkill @ 0x3d910 (252176), 80 B - walk _objPtrs[1.._nextObjId),
   set skill byte on type-4 records with flag p[9]&0x80. */
extern unsigned short w33g_nob;   /* -> _nextObjId */
extern void *w33g_pob[];          /* -> _objPtrs */

void __cdecl w33g_psk(short val)
{
    unsigned short i = 1;
    unsigned int mask;
    unsigned char *p;
    if (w33g_nob > i)
    {
        mask = 0x80;
        do
        {
            p = w33g_pob[i];
            if (p && p[0] == 4 && (p[9] & mask))
                p[0xe2] = (unsigned char)val;
            i++;
        } while (w33g_nob > i);
    }
}
