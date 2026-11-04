/* w44C aa000: _Write@12 — v2: WriteFile result tested with == 1 (FA cmp eax,1)
 * and success/fail shared tail. EBX savers still expected as inserts. */
extern void *handles32[];               /* ?handles32@@3PAPAXA */
extern unsigned short dosError;         /* _dosError */

__declspec(dllimport) int __stdcall WriteFile(void *h, const void *b,
                                              unsigned n, unsigned long *w,
                                              void *ov);

long __stdcall w44c_write(short fd, const void *b, unsigned n)
{
    unsigned long got;
    void *h;
    h = handles32[fd];
    if (h == 0) {
        dosError = 0xffff;
        return -1;
    }
    if (WriteFile(h, b, n, &got, 0) == 1 && got == n) {
        dosError = 0;
        return n;
    }
    dosError = 0xffff;
    return -1;
}