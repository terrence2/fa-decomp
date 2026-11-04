/*
 * w44D_5f460_v1.c — @GRPName@8 @ 0x45f460 (144 B, fpo/esp, cbRegs=2)
 * Fastcall(idx ecx, id edx).  id==0 -> inline strcpy of fTypeOffsets+0xec
 * into wingIds+0xc8; else flags table at LITERAL 0x5421c0 indexed by idx
 * ([ecx+0x5421c0], 8a 81): ==2 -> strcpy fTypeOffsets+0xe0, else
 * _Sprintf(buf, fTypeOffsets+0xd4, id).  Returns wingIds+0xc8.
 */
extern char fTypeOffsets[];
extern unsigned char groupSizes[];
extern char wingIds[];

extern int __cdecl Sprintf(char *buf, const char *fmt, ...);

char * __fastcall GRPName(unsigned long idx, unsigned long id)
{
    if (id == 0) {
        strcpy(wingIds + 0xc8, fTypeOffsets + 0xec);
    } else if (groupSizes[idx] == 2) {
        strcpy(wingIds + 0xc8, fTypeOffsets + 0xe0);
    } else {
        Sprintf(wingIds + 0xc8, fTypeOffsets + 0xd4, id);
    }
    return wingIds + 0xc8;
}