/* w38C 0x268ad v2: stdcall callee (ret 8) so buf[0] reads at [esp] after
 * the call; pre-bool r=1 spelling for mov al,1-before-jge. */
extern void __stdcall w38c_scanfn(unsigned int *c1, unsigned int *c2); /* $FA$_t_4268d8 */
extern char w38c_mcE;                       /* ?mcFlyAll@@3DA + 0x5c8 */
extern void __fastcall w38c_errfn(char *);  /* $FA$_t_424a60 */

char w38c_268ad(void)
{
    unsigned int buf[2];
    char ok = 1;

    w38c_scanfn(buf, buf + 1);
    if ((long)buf[0] < 1) {
        w38c_errfn(&w38c_mcE);
        ok = 0;
    }
    return ok;
}