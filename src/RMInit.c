// _RMInit@0 @ rva 0xa3690 (48 B) — zero 0x67e8 bytes at ?resList@@3PAU...,
//   then the c6 05 flag store resList+0x67e8 = 1 (VA 0x505f08, the memset
//   end byte — dis.py site @0x1b "resList+0x67e8 [human-coin]"; the +0x7e8
//   first draft was a masked-probe slip) lands in the second memset's
//   scheduler slot (CTInit pattern: between mov ecx,0x28 / rep stosd),
//   then zero 0xa0 bytes at ?vdoColorProcess@@3FA+8.
#include <string.h>
extern char resList[];
extern char vdoColorProcess[];
void RMInit_q(void)
{
    memset((char *)resList, 0, 0x67e8);
    resList[0x67e8] = 1;
    memset((char *)vdoColorProcess + 8, 0, 0xa0);
}