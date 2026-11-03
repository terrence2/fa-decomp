/* ?MPLandingStats@@YIXGJ@Z @ rva 0x703e0 (64 B) — fastcall void(ushort,long):
   if (numComputers != 1) { msg[0]=0x2e; *(ushort*)(msg+1)=OBJAlias(id,1);
   *(long*)(msg+3)=stat; snd(-1, msg, 7, 1); } */
extern unsigned long w31d_ncomp;          /* =_numComputers */
extern unsigned short __fastcall w31d_al(unsigned short a, unsigned long b);
    /* =@OBJAlias@8 */
extern void __stdcall w31d_snd(unsigned long dest, void *buf,
                               unsigned long len, unsigned long id);
    /* =$FA$_t_46b260 (MPWrite family) */

void __fastcall MPLandingStatsW(unsigned short id, unsigned long stat)
{
    unsigned char msg[8];
    if (w31d_ncomp != 1) {
        msg[0] = 0x2e;
        *(unsigned short *)(msg + 1) = w31d_al(id, 1);
        *(unsigned long *)(msg + 3) = stat;
        w31d_snd(0xffffffff, msg, 7, 1);
    }
}