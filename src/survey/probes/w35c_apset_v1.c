// w35C #6: ?APSetOffset@@YGXPAUOBJ@@PAUAIRPORT@@PAUOBJ_ON_CARRIER@@@Z @
// rva 0xbae50 (80 B). FA: push ebx / xor eax,eax / push esi / push edi /
// esi=a2(air) / push ebp / edi=a3(occ) / ebp=a1(obj) / ax=[air+0xe6] /
// ebx=objPtrs[ax*4] (sib) / GetRotatedOffsetF24(obj+0x11, op, occ+6)
// (result discarded) / occ+2 = air (param2, NOT op) / occ+0x12 (word) =
// word[obj+0x1d] - word[op+0x1d] / pops ebp,edi,esi,ebx / ret 0xc.
extern long objPtrs[];
extern void __stdcall GetRotatedOffsetF24(long a, long b, long c);

void __stdcall APSetOffsetq(char *obj, char *air, char *occ)
{
    unsigned short i = *(unsigned short *)(air + 0xe6);
    long op = objPtrs[i];

    GetRotatedOffsetF24((long)(obj + 0x11), op, (long)(occ + 6));
    *(long *)(occ + 2) = (long)air;
    *(short *)(occ + 0x12) = *(short *)(obj + 0x1d) - *(short *)(op + 0x1d);
}