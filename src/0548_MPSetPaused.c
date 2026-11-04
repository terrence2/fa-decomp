/* v2: FA saves the flag into bl in the PROLOG (mov bl,cl before the je) —
 * name the register local explicitly.  FA then stores msg[3] AFTER push 1
 * (88 5c 24 0b) and msg[2]=0x11 after push 2 (c6 44 24 0e 11). */
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
    char f;

    f = flag;
    if (numComputers != 1) {
        msg[3] = f;
        msg[2] = 0x11;
        w34c_snd(0xffffffffL, msg + 2, 2, 1);
        w34c_flush(1);
        w34c_pkt[w34c_thisC] = (unsigned char)f;
    }
}