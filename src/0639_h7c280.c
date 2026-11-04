/* w41E_7c280_v1: nameless 96-B chunk @ 0x7c280 (VA 0x47c280), fpo/esp,
 * cbProlog=2 (push esi/edi), 2 params (fastcall ecx=char** p, edx=long* n).
 * FA body: *n=0; skip leading ' '/'\t' incrementing (*p) and (*n);
 * tok=*p; ws=w30d_skipws5(tok) (finds first 0x20/0x09/0x00); terminate;
 * strchr(tok,13) terminates; *n += strlen(tok) (inline repnz scasb).
 * Caller w33H_7c260 (converted) refs $FA$_t_47c280 via map -> my alias.
 */
#include <string.h>

extern char *__fastcall w30d_skipws5(char *p);

void __fastcall w41e_7c280(char **p, long *n)
{
    char *tok;
    char *ws;
    char *cr;
    *n = 0;
    for (;;) {
        char c = **p;
        if (c != ' ' && c != '\t')
            break;
        (*p)++;
        (*n)++;
    }
    tok = *p;
    ws = w30d_skipws5(tok);
    if (ws)
        *ws = 0;
    cr = strchr(tok, 13);
    if (cr)
        *cr = 0;
    *n += strlen(tok);
}