/* w45H 0x872c0: dialog scroll ratio fixup (stdcall, ret 4) */
void __stdcall w45H_872c0(void *arg)
{
    char *esi = (char *)arg;
    int dx = *(short *)(esi + 0xe);
    if (dx == 0)
        return;
    {
        int di;
        if (*(unsigned char *)(esi + 0xb))
            di = (int)(short)(dx - (int)*(unsigned short *)(esi + 0xc));
        else
            di = (int)*(unsigned short *)(esi + 0xc);
        if (*(unsigned char *)(esi + 0xa)) {
            int eax = (int)*(short *)(esi + 0x1c) - (int)*(short *)(esi + 0x14);
            eax = eax * di;
            eax = eax / dx;
            *(unsigned short *)(esi + 0x10) =
                *(unsigned short *)(esi + 0x18) + (unsigned short)eax;
        } else {
            int eax = (int)*(short *)(esi + 0x1e) - (int)*(short *)(esi + 0x16);
            eax = eax * di;
            eax = eax / dx;
            *(unsigned short *)(esi + 0x12) =
                *(unsigned short *)(esi + 0x1a) + (unsigned short)eax;
        }
    }
}