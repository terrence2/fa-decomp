/* w43F 0x79470 v2: comparison polarity flipped to <= with arms swapped, so
 * CL emits cmp / jg (7f) to the LATER (else) arm and the <=-arm inline,
 * matching FA's jg-7f + inline <=-arm arrangement for both ifs.
 * All stores 66 c7 05 imm16.
 */
extern void w43F_GInit(void);
extern unsigned long w43F_curGM;        /* _tempYLR+0x4e70 */
extern short w43F_gmW;                  /* _grMode+0xa */
extern short w43F_gmH;                  /* _grMode+0xc */
extern short w43F_xshiftS;              /* _xshift  0x4e7728 */
extern short w43F_xscaleS;              /* _xscale  0x4e7730 */
extern short w43F_yshiftS;              /* _yshift  0x4e772c */
extern short w43F_yscaleS;              /* _yscale  0x4e7734 */

void w43F_InitGM(long mode)
{
    w43F_curGM = mode;
    w43F_GInit();
    if (w43F_gmW <= (short)0x140) {
        w43F_xshiftS = 1;
        w43F_xscaleS = 0;
    } else {
        w43F_xshiftS = 0;
        w43F_xscaleS = 1;
    }
    if (w43F_gmH <= (short)0xf0) {
        w43F_yshiftS = 1;
        w43F_yscaleS = 0;
    } else {
        w43F_yshiftS = 0;
        w43F_yscaleS = 1;
    }
}
