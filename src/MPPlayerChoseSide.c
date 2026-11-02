/* ?MPPlayerChoseSide@@YIXE@Z @ rva 0x6fef0 (64 B) — fastcall void(char side):
   if (numComputers != 1) { msg[3]=side; msg[2]=0x38;
   snd(0xffffffff, msg+2, 2, 1); MPFlushAll(1); } */
extern unsigned long w28a_ncomp;        /* =_numComputers */
extern void __stdcall w28a_snd(unsigned long dest, void *buf, unsigned long len, unsigned long id);
    /* =$FA$_t_46b260 (MPWrite family) */
extern void __fastcall w28a_flush(unsigned char on);   /* =?MPFlushAll@@YIXD@Z */

void __fastcall w28a_MPPlayerChoseSide(char side)
{
    unsigned char msg[4];
    if (w28a_ncomp != 1) {
        msg[3] = side;
        msg[2] = 0x38;
        w28a_snd(0xffffffff, msg + 2, 2, 1);
        w28a_flush(1);
    }
}
