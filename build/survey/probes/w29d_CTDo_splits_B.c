// v2B: plain inline arg3 (no r var): mvsq(fpfc, fp100, crf()) after the
// statement call crf(); — tests CL's own arg scheduling.
extern char w29d_fte;             /* _serviceTicks+0xec */
extern short w29d_fpfc;           /* _serviceTicks+0xfc */
extern short w29d_fp100;          /* _serviceTicks+0x100 */
extern char w29d_fpf0;            /* _serviceTicks+0xf0 */
extern char w29d_fpf8;            /* _serviceTicks+0xf8 */
extern int w29d_crf(void);        /* $FA$_t_464fc0 */
void __fastcall w29d_mvsq(short a, short b, int c);   /* @MVRSplitS@12 */

int w29d_ctsB(void)
{
    if (w29d_fte)
        return w29d_crf();
    w29d_mvsq(w29d_fpfc, w29d_fp100, w29d_crf());
    w29d_fpfc = w29d_fp100 = 0;
    return w29d_fpf8 = w29d_fpf0 = 1;
}