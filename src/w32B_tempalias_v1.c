/* wave 32 batch B: 0x4bcc0 (unnamed 32 B w/ 14 B junk pads; menu temp-obj aliasser)
   callers: ?MenuStartUp@@Y... (12 call sites)
   FA bytes 0x40bcc0 (18 B code):
   0f bf c1               movsx  eax,cx
   c6 80 e8 82 55 00 01   mov    byte [eax+0x5582e8],1    ; _temp2YLR+0x4d28[ix]
   89 14 85 78 2f 55 00   mov    [eax*4+0x552f78],edx     ; _tempYLR+0x4cc0[ix]
   c3                     ret
   = fastcall(short,ulong): a1(short) in ECX, a2(ulong) in EDX */
extern unsigned char temp2YLR[];
extern unsigned long tempYLR[];

typedef unsigned long ul;

void __fastcall w32b_tempalias(short ix, ul val)
{
    temp2YLR[0x4d28 + ix] = 1;
    tempYLR[0x1330 + ix] = val;
}