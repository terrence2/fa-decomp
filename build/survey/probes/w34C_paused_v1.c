/* ?MPSetPaused@@YIXD@Z @ rva 0x6f070 (454768, 80 B) — fastcall void(char flag):
 * if (numComputers != 1) { buf[3]=flag; buf[2]=0x11; snd(-1, buf+2, 2, 1);
 * flush(1); packetBytes[thisComputer] = flag; }   (12-byte FA tail) */
extern int numComputers;           /* =_numComputers (public, no map) */
extern unsigned long w34c_thisC;   /* =_thisComputer */
extern unsigned char w34c_pkt[];   /* =?packetTicks@@3PAJA+0x4d8 */
extern void __stdcall w34c_snd(unsigned long dest, void *buf,
                               unsigned long len, unsigned long id);
/* =$FA$_t_46b260 (still-stub t0005b, MPWrite family) */
extern void __fastcall w34c_flush(char a);   /* =?MPFlushAll@@YIXD@Z */

void __fastcall MPSetPausedW(char flag)
{
    unsigned char msg[4];

    if (numComputers != 1) {
        msg[3] = flag;
        msg[2] = 0x11;
        w34c_snd(0xffffffffL, msg + 2, 2, 1);
        w34c_flush(1);
        w34c_pkt[w34c_thisC] = (unsigned char)flag;
    }
}