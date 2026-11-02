// _UkraineCheckMaxPlanes @ rva 0x7f2a0 = 520864, 96 B (cdecl; regs
//   esi=walker, ebx=count, edi=best, ebp=max; inner best test reg-left
//   cmp ebp,eax / jg; break test cmp ebx,0xb / jle; decl order
//   (walker, count, best, max) with max-init first so the prologue xors
//   come out ebp, ebx, edi then mov esi.  Patched window 0x4a,15: FA
//   schedules the tail as dec; xor eax; mov ecx,0x2f; cmp ebx,0xb; rep
//   stosd; jg while CL emits xor eax; mov ecx,0x2f; rep stosd; dec;
//   cmp ebx,0xb; jg — same instruction set, scheduler-only reorder
//   (unsteerable; --count inside the while/spellings u3-u9 all sink the
//   dec past the rep).  No reloc sites in the window.)
extern unsigned char w26_rankStr[]; /* map _w26_rankStr=_pilotRanks+0x1ec */
extern unsigned char w26_campArr[]; /* map _w26_campArr=_campaignPilot+0xdb0 */
extern int __cdecl strnicmpQ(const void *s1, const void *s2, unsigned int n); /* map _strnicmpQ=_strnicmp */
extern void *__cdecl memset(void *d, int c, unsigned int n); /* intrinsic - no map */

void w26c_UkraineCheckMaxPlanes_q(void)
{
    unsigned char *walker;
    int count;
    unsigned long best;
    int max;
    do {
        max = 0;
        count = 0;
        best = 0;
        walker = (unsigned char *)w26_campArr;
        do {
            if (*(unsigned short *)(walker + 0xe) != 0) {
                count++;
                if (strnicmpQ(walker, (void *)w26_rankStr, 2) == 0) {
                    int r;
                    r = *(short *)(walker + 0x2e);
                    if (max <= r) {
                        max = r;
                        best = (unsigned long)walker;
                    }
                }
            }
            walker += 0xbc;
        } while ((unsigned long)walker < 0x4f6778u);
        if (count <= 11)
            break;
        --count;
        memset((void *)best, 0, 188);
    } while (count > 11);
}/* patch 74,15,4b33c0b92f00000083fb0bf3ab7fab */

// patch 0x3f,4,00000000,0x0:6:w26_campEnd — synthetic DIR32: FA's
//   cmp esi,0x4f6778 imm32 = VA(_campaignPilot)+0x1c60 carries a HIGHLOW
//   for _campaignPilot; the C literal compiles byte-exact but reloc-less
//   (wave-20 literal-VA trap). Newsite binds map TO _w26_campEnd
//   (_campaignPilot+0x1c60; pre-addend content 0 — fitobj bakes the
//   +0x1c60, link writes 0x4f6778) restoring the .reloc entry. */