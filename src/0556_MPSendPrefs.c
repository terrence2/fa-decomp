// ?MPSendPrefs@@YGXXZ @ rva 0x70120 (96 B; FPO locals 3; code 92 B +
// 11 B lea pad).  stdcall void.  if (numComputers == 1 || thisComputer > 0)
// return; else local 9-B block: blk[0] = 0x36 (c6 44 24 00), blk[1..4] =
// _gamePrefs & 0x116e25ff (25 imm form), blk[5..8] = _gameMultiPrefs &
// 0x3403f; stdcall 4-arg call _w43H_send@16(0xffffffff, blk, 9, 1) to the
// stub t0005b gap chunk VA 0x46b260; then ecx=1 fastcall ?MPFlushAll@@YIXD@Z.
extern long w43H_numC;        /* =_numComputers */
extern long w43H_thisC;       /* =_thisComputer */
extern long w43H_gPrefs;      /* =_gamePrefs */
extern long w43H_gMPref;      /* =_gameMultiPrefs */
extern void __stdcall w43H_send(long a, unsigned char *blk, long b, long c); /* =_w43H_send@16=$FA$_t_46b260 */
extern void __fastcall w43H_flush(long n); /* =@w43H_flush@4=?MPFlushAll@@YIXD@Z */

void __stdcall w43H_MPSendPrefs5(void)
{
    unsigned char blk[9];
    unsigned long a, b;
    if (w43H_numC == 1)
        return;
    if (w43H_thisC > 0)
        return;
    blk[0] = 0x36;
    a = w43H_gPrefs & 0x116e25ff;
    *(unsigned long *)(blk + 1) = a;
    b = w43H_gMPref & 0x3403f;
    *(unsigned long *)(blk + 5) = b;
    w43H_send(0xffffffff, blk, 9, 1);
    w43H_flush(1);
}