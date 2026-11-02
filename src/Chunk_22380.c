// w26a_22380 @ rva 0x22380 (140416, unnamed 17 B orphan) — FA bytes (raw):
//   57                   push edi
//   33 c0                xor eax,eax
//   bf 88 1e 53 00       mov edi, 0x531e88        (_specials)
//   b9 32 00 00 00       mov ecx, 0x32
//   f3 ab                rep stosd
//   5f                   pop edi
//   c3                   ret
// 17 B, no tail pad. Inline memset of the _specials block, 0xc8 bytes
// (FPSInit recipe: memset of a constant size -> rep stosd).
#include <string.h>
extern char specials_t[];
void w26a_22380(void)
{
    memset(specials_t, 0, 0xc8);
}