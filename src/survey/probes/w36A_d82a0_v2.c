// w36A_d82a0_v2: no m staging for the RMW (v1 staged mode in `m`, then
// CL reloaded the field for &= and stored it back late; FA emits direct
// and [esi+0xc],0xfffffbf7 after the free call). Field-statement order
// follows FA: h=0, mode&=, buf=0, d4=0. Nested ifs keep FA's two test
// al,0x83 / test al,8 branch structure.

struct FILEBUFC {
    unsigned long h;
    unsigned long d4;
    unsigned long buf;
    unsigned long mode;
};

extern void __cdecl free(void *);

void __cdecl fcloseUnk2(struct FILEBUFC *fp)
{
    if ((fp->mode & 0x83) != 0) {
        if ((fp->mode & 0x8) != 0) {
            free(fp->buf);
            fp->h = 0;
            fp->mode &= ~0x408;
            fp->buf = 0;
            fp->d4 = 0;
        }
    }
}