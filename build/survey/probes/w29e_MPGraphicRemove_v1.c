/* ?MPGraphicRemove@@YGXXZ @ rva 0x6fe70 (64 B) — stdcall void(void):
   if (numComputers != 1) {
       msg[0]=0x25; msg[1w]=OBJAlias(curId, 1)  [fastcall, curId word load];
       snd(-1, msg, 3, 1); }
   (the 66 8b 0d load of _curId is one of the bytes dis.py elides.) */
extern long w29e_nc;              /* =_numComputers */
extern unsigned short w29e_cid;   /* =_curId */
extern unsigned short __fastcall w29e_al(unsigned short a, unsigned long b);
                                  /* =@OBJAlias@8 */
extern void __stdcall w29e_snd(long a, unsigned char *b, long c, long d);
                                  /* =$FA$_t_46b260 */

void __stdcall MPGraphicRemoveW(void)
{
    unsigned char msg[4];
    if (w29e_nc != 1) {
        msg[0] = 0x25;
        *(unsigned short *)(msg + 1) = w29e_al(w29e_cid, 1);
        w29e_snd(-1, msg, 3, 1);
    }
}