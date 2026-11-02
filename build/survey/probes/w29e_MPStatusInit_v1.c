/* ?MPStatusInit@@YIXXZ @ rva 0x70460 (64 B) — thiscall void(this):
   inline-memset four 32-byte blocks: mpStatusToDraw[0],draw[+0xc0] fill
   0xffffffff, mpStatus[0] fill 0x03030303, draw[+0xa0] fill 0x03030303
   (eax holds the dword fill; rep stosd ecx=8). */
extern long w29e_msd[];    /* =?mpStatus@@3PAJA (+0) */
extern long w29e_msdD[];   /* =?mpStatusToDraw@@3PAJA */
void *memset(void *d, int v, unsigned int n);

void MPStatusInitW(void)
{
    memset(w29e_msdD, 0xff, 32);
    memset(w29e_msdD + 48, 0xff, 32);
    memset(w29e_msd, 3, 32);
    memset(w29e_msdD + 40, 3, 32);
}