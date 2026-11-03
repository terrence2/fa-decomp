/* ?MPSendGameMode@@YGXXZ @ rva 0x6eee0 (64 B) — stdcall void(void):
   if (numComputers != 1) { if (thisComputer == 0) {
       msg[3]=gameMode; msg[2]=0x4b; snd(-1, msg+2, 2, 1); } } */
extern unsigned long w31d_ncomp;          /* =_numComputers */
extern unsigned long w31d_thisComp;       /* =_thisComputer */
extern unsigned char w31d_gameMode;       /* =_gameMode */
extern void __stdcall w31d_snd(unsigned long dest, void *buf,
                               unsigned long len, unsigned long id);
    /* =$FA$_t_46b260 (MPWrite family) */

void __stdcall MPSendGameModeW(void)
{
    unsigned char msg[4];
    if (w31d_ncomp != 1) {
        if (w31d_thisComp == 0) {
            msg[3] = w31d_gameMode;
            msg[2] = 0x4b;
            w31d_snd(0xffffffff, msg + 2, 2, 1);
        }
    }
}