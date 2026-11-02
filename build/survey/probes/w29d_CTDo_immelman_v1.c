// _CTDo_immelman @ rva 0x65750 (80 B). Same shape as _CTDo_splits but
// calls @MVRImmelman@12 (0x4a9b70).
extern char w29d_fte;             /* _serviceTicks+0xec */
extern short w29d_fpfc;           /* _serviceTicks+0xfc */
extern short w29d_fp100;          /* _serviceTicks+0x100 */
extern char w29d_fpf0;            /* _serviceTicks+0xf0 */
extern char w29d_fpf8;            /* _serviceTicks+0xf8 */
extern int w29d_crf(void);        /* $FA$_t_464fc0 */
void __fastcall w29d_mviq(short a, short b, int c);   /* @MVRImmelman@12 */

int w29d_cti(void)
{
    short t;

    if (w29d_fte)
        return w29d_crf();
    w29d_crf();
    t = w29d_fp100;
    w29d_mviq(w29d_fpfc, t, w29d_crf());
    w29d_fpfc = w29d_fp100 = 0;
    return w29d_fpf0 = w29d_fpf8 = 1;
}