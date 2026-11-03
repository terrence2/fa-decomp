/* ?MPFortButton@@YIXJJ@Z @ rva 0x6ffe0 (48 B) — fastcall void(long,long):
   if (numComputers != 1) { *(long*)(msg+1)=btn; *(long*)(msg+5)=val;
   msg[0]=0x3c; snd(-1, msg, 9, 1); }
   (NO MPFlushAll here — that is MPPlayerChoseFort's shape; FA 0x46ffe0
   tails straight add esp,0xc / ret / 8b ff pad, v2 proved it.) */
extern unsigned long w31d_ncomp;          /* =_numComputers */
extern void __stdcall w31d_snd(unsigned long dest, void *buf,
                               unsigned long len, unsigned long id);
    /* =$FA$_t_46b260 (MPWrite family) */

void __fastcall MPFortButtonW(long btn, long val)
{
    unsigned char msg[12];
    if (w31d_ncomp != 1) {
        *(unsigned long *)(msg + 1) = btn;
        *(unsigned long *)(msg + 5) = val;
        msg[0] = 0x3c;
        w31d_snd(0xffffffff, msg, 9, 1);
    }
}