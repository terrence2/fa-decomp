// 0x8b450 _SAYInit2@0 — v1
extern unsigned short w29fSayW;   /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x18 */
extern char w29fHome;             /* -> _home */
extern char w29fCur;              /* -> ?cursorOn@@3DA+0x8 */
extern char w29fCT;               /* -> ?COMMENT_TYPE@@3W4__unnamed@@A+0x10 */
extern int __stdcall w29fMISS(void);

void __stdcall SAYInit2X(void)
{
    int r;
    w29fSayW = 0;
    w29fHome = 0;
    w29fCur = 0;
    w29fCT = 0;
    r = w29fMISS();
    if (r > 0) {
        w29fHome = 1;
        w29fCT = 1;
    } else if (r < 0) {
        w29fCur = 1;
    }
}