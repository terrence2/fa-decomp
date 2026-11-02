/* probe v1: call __getptd; add eax,0xc; ret */
extern char *_getptd(void);
char *w24b_chunkd99c0(void) { return _getptd() + 12; }
