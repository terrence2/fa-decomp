/* _SAYInit@0 @ 0x8b410 — v1: chained zero assignment, rightmost stores first */
extern unsigned short sayF1;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0xc  */
extern unsigned short sayF2;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x7c */
extern unsigned short sayF3;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x8  */
extern unsigned short sayF4;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x14 */
extern unsigned short sayF5;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x4  */
extern unsigned short sayF6;   /* -> _checkRightButton+0x2480 */
extern unsigned short sayF7;   /* -> _checkRightButton+0x247c */
extern unsigned short sayF8;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0xfc */

void __stdcall SAYInit_sa(void)
{
    sayF8 = sayF7 = sayF6 = sayF5 = sayF4 = sayF3 = sayF2 = sayF1 = 0;
}
