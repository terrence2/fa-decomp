// _CTDo_splits @ rva 0x65700 (80 B).
// FA: a0 [+0xec] / 84 c0 / 74 05 / e9 [$FA$_t_464fc0] / e8 [$FA$_t_464fc0] /
// 66 8b 15 [+0x100] / 50 / 66 8b 0d [+0xfc] / e8 [@MVRSplitS@12] / 33 c0 /
// 66 a3 [+0x100] / 66 a3 [+0xfc] / b8 01 00 00 00 / a2 [+0xf0] / a2 [+0xf8] /
// c3. Tail pad 8d642400+8da42400000000 (11 B).
extern char w29d_fte;             /* _serviceTicks+0xec */
extern short w29d_fpfc;           /* _serviceTicks+0xfc */
extern short w29d_fp100;          /* _serviceTicks+0x100 */
extern char w29d_fpf0;            /* _serviceTicks+0xf0 */
extern char w29d_fpf8;            /* _serviceTicks+0xf8 */
extern int w29d_crf(void);        /* $FA$_t_464fc0 */
void __fastcall w29d_mvsq(short a, short b, int c);   /* @MVRSplitS@12 */

int w29d_cts(void)
{
    short t;

    if (w29d_fte)
        return w29d_crf();
    w29d_crf();
    t = w29d_fp100;
    w29d_mvsq(w29d_fpfc, t, w29d_crf());
    w29d_fpfc = w29d_fp100 = 0;
    return w29d_fpf0 = w29d_fpf8 = 1;
}