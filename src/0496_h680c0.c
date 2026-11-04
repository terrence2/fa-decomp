/* w36F 0x680c0 (64B, tail 8bff) v1 — thisfastcall memset+tag+strcpy pilot init
 * FA: push esi; mov edx,ecx; push edi; xor eax,eax; mov edi,edx;
 * mov ecx,0x978; rep stosd; mov ecx,-1; sub eax,eax; mov byte[edx],0xf;
 * mov edi,[pilotRanks]; repnz scasb; not ecx; sub edi,ecx; mov eax,ecx;
 * shr ecx,2; mov esi,edi; lea edi,[edx+0xa2]; rep movsd; mov ecx,eax;
 * and ecx,3; rep movsb; pop edi; pop esi; ret
 */
#include <string.h>
extern char *pilotRanks;   /* bare public _pilotRanks @ 0x4f7408 */

void __fastcall w36f_initpilot(char *thisp)
{
    memset(thisp, 0, 0x25e0);
    thisp[0] = 0x0f;
    strcpy(thisp + 0xa2, pilotRanks);
}