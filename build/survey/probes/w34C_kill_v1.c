/* ?MPKillStats@@YIXGG@Z @ rva 0x70390 (459664, 80 B) — fastcall
 * void(unsigned short alias, unsigned short target):
 * if (numComputers != 1) { buf[0]=0x2d; store u16 buf[1..2]=OBJAlias(a1,1);
 * buf[3..4]=OBJAlias(a2,1); snd(-1, buf, 5, 1); }   (5-byte FA tail) */
extern int numComputers;           /* =_numComputers (public, no map) */
extern unsigned short __fastcall w34c_objal(unsigned short, unsigned long);
/* =@OBJAlias@8 (fastcall, 8 B nominal) */
extern void __stdcall w34c_snd(unsigned long dest, void *buf,
                               unsigned long len, unsigned long id);
/* =$FA$_t_46b260 (still-stub t0005b, MPWrite family) */

void __fastcall MPKillStatsW(unsigned short a1, unsigned short a2)
{
    unsigned char msg[8];

    if (numComputers != 1) {
        msg[0] = 0x2d;
        *(unsigned short *)(msg + 1) = w34c_objal(a1, 1);
        *(unsigned short *)(msg + 3) = w34c_objal(a2, 1);
        w34c_snd(0xffffffffL, msg, 5, 1);
    }
}