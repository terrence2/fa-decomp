/* w34A @ rva 0x84ad0 (dec 543440), 32 B, FPO fpo/esp prolog=0, unnamed.
 * FA bytes: fld qword [0x4e5410] / fdiv qword [0x4e5418] / fstp qword
 * [_timerTicks+4] / ret + 13 B census pad (8d9b...+8da4...).
 * constants live in FA's .rdata: +0x3bc = 86400000.0, +0x3c4 = 1572480.0
 * (= 55.0).  x87 plain double divide: ((double*)&timerTicks)[+4] = A/B.
 */
extern int w34_cA;          /* .rdata 0x4e5410 (804000.0/... const) */
extern int w34_cB;          /* .rdata 0x4e5418                      */
extern long timerTicks;     /* 0x549e3c, store hits +0x4            */

void w34_84ad0(void)
{
    *(double *)((char *)&timerTicks + 4) =
        *(double *)&w34_cA / *(double *)&w34_cB;
}