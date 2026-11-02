/* ?spxaddr2str@@YADPAUNET_ADDRESS@@PAD@Z @ 0x95380 — v1 */
extern char *__cdecl w28b_hbtoa(unsigned char *src, unsigned char n, char *dst);  /* -> ?hbtoa@@YAPADPAEFPAD@Z */

char w28b_spx_f(void *addr, char *buf)
{
    char *p;
    if (*(unsigned short *)addr != 2)
        return 0;
    p = w28b_hbtoa((unsigned char *)((char *)addr + 4), 4, buf);
    w28b_hbtoa((unsigned char *)((char *)addr + 8), 6, p);
    return 1;
}
