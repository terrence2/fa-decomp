// _CancelCmdBuf@0 @ rva 0x63010 (80 B) — stdcall void(void).
// FA: 66 c7 05 [+0x62] ffff / 66 c7 05 [+0x58] ffff / b8 07 00 00 00 /
// 8a 0d [_curThing] / a2 [+0x51] / a2 [+0x50] / 33 c0 / 80 f9 02 /
// 66 a3 [+0x54] / 66 a3 [+0x52] / 74 05 / 80 f9 04 / 75 05 / e9
// [_CTRespondToCancelCmdBuf@0] / c3. Tail pad 8d642400+8da42400000000.
extern char w29d_c0;              /* _curThing */
extern char w29d_b50;             /* _curThing+0x50 */
extern char w29d_b51;             /* _curThing+0x51 */
extern short w29d_w54;            /* _curThing+0x54 */
extern short w29d_w52;            /* _curThing+0x52 */
extern short w29d_w58;            /* _curThing+0x58 */
extern short w29d_w62;            /* _curThing+0x62 */
extern void __stdcall w29d_crq(void);   /* _CTRespondToCancelCmdBuf@0 */

void __stdcall w29d_ccb(void)
{
    w29d_w62 = -1;
    w29d_w58 = -1;
    w29d_b50 = w29d_b51 = 7;
    if (w29d_c0 == 2 || w29d_c0 == 4) {
        w29d_crq();
        return;
    }
    w29d_w54 = w29d_w52 = 0;
}