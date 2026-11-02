// _UkraineCheckMaxPlanes @ rva 0x7f2a0 = 520864, 96 B (decl order for slots
//   ebx=count, esi=walker, edi=best, ebp=max; campEnd compared as literal
//   against walker (cmp esi,imm); memset as INTRINSIC (xor eax; mov ecx,
//   0x2f; rep stosd on edi); one do-while: scan; if count<=11 break;
//   --count; fill; while count>11 re-scan).
extern unsigned char w26_rankStr[]; /* map _w26_rankStr=_pilotRanks+0x1ec */
extern unsigned char w26_campArr[]; /* map _w26_campArr=_campaignPilot+0xdb0 */
extern int __cdecl strnicmpQ(const void *s1, const void *s2, unsigned int n); /* map _strnicmpQ=_strnicmp */
extern void *__cdecl memset(void *d, int c, unsigned int n); /* intrinsic - no map */

void w26c_UkraineCheckMaxPlanes_q(void)
{
    int count;
    unsigned char *walker;
    unsigned long best;
    int max;
    do {
        count = 0;
        walker = (unsigned char *)w26_campArr;
        best = 0;
        max = 0;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                int r;
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    r = *(short *)(walker + 0x2e);
                    if (r >= max) {
                        max = r;
                        best = (unsigned long)walker;
                    }
                }
            }
            walker += 0xbc;
        } while ((unsigned long)walker < 0x4f6778);
        if (count <= 11)
            break;
        count--;
        memset((void *)best, 0, 188);
    } while (count > 11);
}