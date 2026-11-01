// _ZONEInit@0 @ rva 0x217b0 (16 B) — mov word[cobraData+0xc1c0],0 / ret
//   (the anchor is a C++-mangled struct pointer; --map retargets our raw
//   CL symbol)
extern unsigned char cobraData_x[];

void __stdcall ZONEInit(void)
{
    *(unsigned short *)(cobraData_x + 0xc1c0) = 0;
}
