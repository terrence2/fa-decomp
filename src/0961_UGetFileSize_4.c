// 0xaa080 — v3: Open/Close are fastcall (FA: xor edx,edx; e8 with no pushes)
extern char *w28c_hndT[];
extern unsigned short __fastcall w28c_uOpen(unsigned long a, unsigned long b);
extern void __fastcall w28c_uClose(unsigned short h);
extern unsigned long __stdcall w28c_gfs(void *h, unsigned long *hi);
extern unsigned short w28c_dosErrT;

unsigned long __fastcall w28c_uGetFileSize(unsigned long fd)
{
    short h;
    unsigned long r;

    if ((h = w28c_uOpen(fd, 0)) == -1) return 0xffffffffUL;
    r = w28c_gfs(w28c_hndT[h], 0);
    w28c_uClose(h);
    if (r == 0xffffffffUL) { w28c_dosErrT = 0xffff; return 0xffffffffUL; }
    w28c_dosErrT = 0;
    return r;
}
