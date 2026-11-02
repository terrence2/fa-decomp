/* Ispunct - FA rva 0xd41d0 (868816) - EXACT probe verdict, tier1_a_r5.json entry 'Ispunct_v4'
 * Form: patch-hybrid
 * Levers: ctype gate 83 3d via __ctype+0x204 addend + reg fixes + 18->20-byte tail
 * Maps: _ctype204=__ctype+0x204
 * patch 0: 8->7 B 83 3d 00000000 01, DIR32 re-add _ctype204
 * patch 0xa: -> 4c
 * patch 0xf: -> 51
 * patch 0x19: 18->20 B 8b 15 ... 33 c0 ... c3, DIR32 re-add __pctype
 * Probes: v1-v4
 */
extern char ctype204[];
extern unsigned short *_pctype;
extern int __cdecl _isctype(int c, int mask);

int __cdecl ispunct(int c)
{
    if (*(int *)ctype204 > 1)
        return _isctype(c, 0x10);
    return _pctype[c] & 0x10;
}
