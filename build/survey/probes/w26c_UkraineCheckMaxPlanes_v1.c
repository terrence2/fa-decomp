// _UkraineCheckMaxPlanes @ rva 0x7f2a0 = 520864, 96 B (push ebx/esi/edi/ebp;
// Ltop: ebp=ebx=edi=0; esi=0x4f58c8(_campaignPilot+0xdb0); do { if WORD
// [esi+0xe]!=0: inc ebx; strnicmp(esi,_pilotRanks+0x1ec,2)==0 -> int r =
// (short)[esi+0x2e]; if (ebp<=r) { ebp=r; edi=esi; } esi+=0xbc } while
// (esi<0x4f6778(_campaignPilot+0x1c60)); if (ebx<=11) break; --ebx;
// memset(edi,0,188) as xor eax/mov ecx,0x2f/cmp ebx,0xb/rep stosd;
// jg (dead) back to Ltop; pop×4; ret.
extern unsigned char w26_rankStr[]; /* map _w26_rankStr=_pilotRanks+0x1ec */
extern unsigned char w26_campArr[]; /* map _w26_campArr=_campaignPilot+0xdb0 */
extern unsigned char w26_campEnd[]; /* map _w26_campEnd=_campaignPilot+0x1c60 */
extern int __cdecl strnicmpQ(const void *s1, const void *s2, unsigned int n); /* map _strnicmpQ=_strnicmp */
extern void *__cdecl memset0(void *d, int c, unsigned int n); /* map _memset0=memset */

void w26c_UkraineCheckMaxPlanes_q(void)
{
    unsigned long best;
    int ebp, ebx, i;
    do {
        unsigned char *esi = w26_campArr;
        ebp = 0;
        ebx = 0;
        best = 0;
        do {
            if (*(unsigned short *)(esi + 0xe) != 0) {
                int r;
                ebx++;
                if (strnicmpQ(esi, (void *)w26_rankStr, 2) == 0) {
                    r = *(short *)(esi + 0x2e);
                    if (r >= ebp) {
                        ebp = r;
                        best = (unsigned long)esi;
                    }
                }
            }
            esi += 0xbc;
        } while ((unsigned long)esi < (unsigned long)w26_campEnd);
        if (ebx > 11) {
            ebx--;
            memset0((void *)best, 0, 188);
        } else break;
    } while (ebx > 11);
}