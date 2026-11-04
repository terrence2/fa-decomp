/* w46D Getdays rva 920736 (0x4e0ca0) v1 */
extern unsigned __cdecl strlen(const char*);
extern char* __cdecl strcpy(char*, const char*);
extern void* __cdecl malloc(unsigned);
extern char** w46d_tbl;   /* map: _w46d_tbl=__newmode+0xfc */

char* __cdecl w46d_getdays_q(void)
{
    char** t; char** q; char* p; char* c; int tot; int j;
    t = w46d_tbl;
    q = t + 7;
    tot = 0; j = 7;
    do { tot += strlen(q[-7]) + strlen(q[0]) + 2; q++; } while (--j);
    ++tot;
    p = (char*)malloc(tot);
    if (p != 0) {
        c = p; j = 7;
        do {
            *c = ':'; c++;
            strcpy(c, *t); c += strlen(c);
            *c = ':'; c++;
            strcpy(c, t[7]); c += strlen(c);
            t++;
        } while (--j);
        *c = 0;
    }
    return p;
}