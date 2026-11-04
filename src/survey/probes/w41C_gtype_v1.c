// w41C candidate 0x5e160 (0x45E160, 48 B code) — twin of @GRPSetType@4
// (rva 0x5ee90, converted EXACT in w4probe) with _WNGPart@12 swapped for
// _GRPPart@12.  FA raw bytes identical except the helper call disp.
//   66 a1 <_curId> (mov ax,[curId]) / 6a 00 / 6a 00 /
//   88 0d <_curThing+0xfc> (mov byte [curThing+0xfc],cl — fastcall param,
//   hidden from dis.py's byte-granularity scan, decoded from raw) /
//   50 (push eax) / e8 _WNGPart@12 / 3c 01 (cmp al,1) / 75 23 (jne exit) /
//   MSGSend pushes 1/&curThing+0xfc/9/0x8000/0/0/0x8001/eax (call _MSGSend@32) /
//   c3 / 8b ff tail.
extern char curThing[];
extern unsigned short curId;

extern char __stdcall WNGPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall w41C_wngType(char type)
{
    *(char *)(curThing + 0xfc) = type;
    if (WNGPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 9, curThing + 0xfc, 1);
}