/* _SeekTell@12 @ 0xa9ec0 (140 B code + 8d 64 24 00 pad): low-level tell read.
 * long __stdcall SeekTell(int fd, int whence, long off):
 *   h = handles32[(short)fd];        [0f bf 44 24 04 movsx eax,word arg1;
 *                                     8b 0c 85 607d5700 indexed load]
 *   if (h == 0) { dosError = -1 (66 c7 05 word store); return -1; }
 *   x (UNINIT local, sub esp,4) switch ((unsigned char)whence):
 *     0: x=0 (33 c0) / 1: x=1 (b8 1) / 2: x=2 (b8 2) / default: x = local
 *     home slot [8b 44 24 04 - read of never-stored local];
 *   r = SetFilePointer(h, off, NULL, x);  [ff 15 IAT call, stdcall, no clean;
 *     push order: eax(x) as arg4 first, 6a 00 (NULL), off, handle last]
 *   if (r == -1) { dosError = -1; return -1; }
 *   dosError = 0; return r.
 * push ebx save even though ebx unused (FA prologue artifact: 53 after test,
 * before jne; 5b before both ret paths).
 */
extern void *handles32[];
extern short dosError;
extern long __stdcall SetFilePointer(long h, long off, void *high, unsigned long meth);

long __stdcall SeekTell(int fd, int whence, long off)
{
    long x;
    long h, r;

    h = (long)handles32[(short)fd];
    if (h == 0) {
        dosError = -1;
        return -1;
    }
    switch ((unsigned char)whence) {
    case 0:
        x = 0;
        break;
    case 1:
        x = 1;
        break;
    case 2:
        x = 2;
        break;
    }
    r = SetFilePointer(h, off, 0, (unsigned long)x);
    if (r == -1) {
        dosError = -1;
        return -1;
    }
    dosError = 0;
    return r;
}