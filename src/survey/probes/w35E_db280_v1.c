// chunk @ rva 0xdb280 (43 B) -- skip whitespace: c = *cnt? no...
// do { push arg2; ++*p1; c = $FA$_t_4db230(arg2); } while (isspace(c));
// fpo/esp, saves ebx esi edi; returns last c (ebx).
extern int nextw(char *);                        /* $FA$_t_4db230, cdecl */
extern int isspace(int);

int w35_db280(int *cnt, char *arg)
{
    int c;
    c = c;
    do {
        ++*cnt;
        c = nextw(arg);
    } while (isspace(c));
    return c;
}