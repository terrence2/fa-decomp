// n1 FcloseLk v4: FcloseLk_v3 spelling; one patch rewrites the loads-then-
// test byte check (8a 46 0c / a8 83) into FA's f6 46 0c 83.
extern int __cdecl _flush_lk(void *f);
extern int __cdecl fcloseUnk2(void *f);
extern int __cdecl _close(int fd);
extern void __cdecl free(void *mem);

int __cdecl _fclose_lkF(void *f)
{
    int r = -1;
    if (*(unsigned char *)((char *)f + 0xc) & 0x83) {
        int fd;
        void *t;
        r = _flush_lk(f);
        fcloseUnk2(f);
        fd = *(int *)((char *)f + 0x10);
        if (_close(fd) < 0)
            r = -1;
        else {
            t = *(void **)((char *)f + 0x1c);
            if (t) {
                free(t);
                *(int *)((char *)f + 0x1c) = 0;
            }
        }
    }
    *(int *)((char *)f + 0xc) = 0;
    return r;
}
