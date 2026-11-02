extern int __stdcall Dist(void *a, void *b);
extern void **objPtrs;
extern unsigned char mainV[];
char __fastcall PROJAccurateHardPos(int id)
{
    char *o;
    o = (char *)objPtrs[id & 0xffff];
    if ((unsigned char)o[0x10] & 0x80) return 1;
    if (*(unsigned short *)(mainV + 0x1c) == 0
        || *(unsigned short *)(mainV + 0x1e) == 0) return 1;
    return (char)(Dist(o + 0x11, mainV + 0x20) <= 0x138800);
}