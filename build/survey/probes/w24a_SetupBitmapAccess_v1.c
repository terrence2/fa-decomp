extern unsigned char brsColorProcess_x[];
extern unsigned __int64 averageTest_x;

void __stdcall SetupBitmapAccess(short a, short b, short c)
{
    *(short *)(brsColorProcess_x) = a;
    *(short *)((char *)&averageTest_x + 0x1c) = b;
    *(short *)((char *)&averageTest_x + 0x18) = c;
}
