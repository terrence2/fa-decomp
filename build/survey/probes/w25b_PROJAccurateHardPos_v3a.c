extern int __stdcall Dist(void *a, void *b);
extern void *objPtrs[];
extern unsigned char mainV[];
char __fastcall PROJAccurateHardPos(int id)
{
    int idm;
    idm = id;
    idm &= 0xffff;
    if ((unsigned char)objPtrs[idm][0x10] & 0x80) return 1;
    if (*(unsigned short *)(mainV + 0x1c) != (unsigned short)id
        && *(unsigned short *)(mainV + 0x1e) != (unsigned short)id) return 0;
    return (char)(Dist(objPtrs[idm], mainV + 0x20) <= 0x138800);
}