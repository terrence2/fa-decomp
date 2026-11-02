/* BasicLinkSound - FA rva 0x33120 (209184) - EXACT probe verdict, tier1_a_r2.json entry 'BasicLinkSound_v2'
 * Form: plain C
 * Levers: vol expression inlined into arg stream
 * Maps: _radioVol=?radioVol@@3GA, _SoundOn@60=?SoundOn@@YGFPADFFDGFFDFFGGFEF@Z
 * Probes: v1,v2
 */
extern unsigned short radioVol;
extern char __stdcall SoundOn(char *s, int a1, int a2, int a3, int a4, int a5,
                              int a6, int a7, int a8, int a9, int a10, int a11,
                              int a12, int a13, int a14);

char __fastcall BasicLinkSound(char *s, int x)
{
    return SoundOn(s, 0xff,
                   (int)((long)(((unsigned long)radioVol << 8)
                                - (unsigned long)radioVol)
                        / 100),
                   0, 0, -1, -1, 0, 0, -1, 0xffff, 0xffff, 0, 0, x);
}
