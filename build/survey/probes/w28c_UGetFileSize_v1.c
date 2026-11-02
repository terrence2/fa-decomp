// 0xaa080 @UGetFileSize@4 (96 B) — v1: fastcall, fd in ecx; Open(fd,0) via ecx/edx
extern char *w28c_hndT[];          /* ?handles32@@3PAPAXA (word counter at -4) */
extern unsigned short __fastcall w28c_uOpen(unsigned long a, unsigned long b);
extern void __fastcall w28c_uClose(unsigned short h);
extern unsigned long __stdcall w28c_gfs(void *h, unsigned long *hi);
extern unsigned short w28c_dosErrT;

unsigned long __fastcall w28c_uGetFileSize(unsigned long fd)
{
    unsigned short h;
    unsigned long r;

    if ((h = w28c_uOpen(fd, 0)) == 0xffff) return 0xffffffffUL;
    r = w28c_gfs(w28c_hndT[h], 0);
    w28c_uClose(h);
    if (r == 0xffffffffUL) { w28c_dosErrT = 0xffff; return 0xffffffffUL; }
    w28c_dosErrT = 0;
    return r;
}
