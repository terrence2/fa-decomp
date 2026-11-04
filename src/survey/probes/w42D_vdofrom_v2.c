// ?VDOfromVDOHEADER@@YADPAUVDO@@PAUVDOHEADER@@@Z @ rva 0xac1d0 (128 B)
// v2: if(c) vdoExitCode=5 moved to FA's position (after vd[0x18] copy)
extern short vdoExitCode;           /* ?vdoExitCode@@3FA */

char w42D_vdofrom(char *vd, char *vh)
{
    unsigned char c;
    unsigned short w;

    c = *(unsigned char *)(vh + 9);
    *(char *)(vd + 0xc) = c;
    *(unsigned short *)vd = *(unsigned short *)(vh + 0x12);
    *(unsigned short *)(vd + 2) = *(unsigned short *)(vh + 0x14);
    w = (unsigned short)(0x100 / (char)vh[8]);
    *(unsigned short *)(vd + 4) = w;
    *(unsigned short *)(vd + 8) = *(unsigned short *)(vh + 0x10);
    *(char *)(vd + 0xa) = *(char *)(vh + 0xe);
    *(char *)(vd + 0xb) = *(char *)(vh + 0xf);
    *(unsigned short *)(vd + 0x16) = *(unsigned short *)(vh + 0x18);
    *(unsigned short *)(vd + 0x1a) = *(unsigned short *)(vh + 0x1c);
    *(unsigned short *)(vd + 6) = 0;
    *(unsigned short *)(vd + 0x18) = *(unsigned short *)(vh + 0x1a);
    if (c != 0)
        vdoExitCode = 0x5;
    return (unsigned char)vd[0xc] == 0;
}