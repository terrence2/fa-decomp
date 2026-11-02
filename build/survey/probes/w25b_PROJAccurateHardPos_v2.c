extern int __stdcall Dist(void *a, void *b);
extern void *objPtrs[];
extern unsigned char mainV[];
char __fastcall PROJAccurateHardPos(int id)
{
    int idm;
    char *o;
    idm = id;
    idm &= 0xffff;
    o = (char *)objPtrs[idm];
    if ((unsigned char)o[0x10] & 0x80) return 1;
    if (*(unsigned short *)(mainV + 0x1c) == (unsigned short)id
        || *(unsigned short *)(mainV + 0x1e) == (unsigned short)id) return 1;
    return (char)(Dist(o + 0x11, mainV + 0x20) <= 0x138800);
}