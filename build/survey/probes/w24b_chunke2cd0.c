/* probe v1: call __getptd; add eax,0x58; ret */
extern char *_getptd(void);
char *w24b_chunke2cd0(void) { return _getptd() + 0x58; }
