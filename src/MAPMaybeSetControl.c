// MAPMaybeSetControl @ rva 0x21e60 — decompiled from FA.EXE (probe d222_msc3.c, byte-exact)
extern void *objPtrs[];
extern void __stdcall OBJSetControl(int a, int b, int c, int d);
extern void mscTail(void);
void __fastcall MAPMaybeSetControl_q(int p1, int p2)
{
    if ((unsigned short)p2 == 0
        || !(*(unsigned char *)((char *)objPtrs[p2 & 0xffff] + 0x10) & 0x80))
    {
        OBJSetControl(p1, p2, 1, 1);
        mscTail();
    }
}
