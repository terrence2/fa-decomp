// w44G @ 0x460240 (rva 0x60240, 80 B, unnamed, ret 0x10 stdcall-shaped,
// 4 args, fpo/esp, no abs fixups). G_SetColor(a) then two G_Rect panels:
//   G_Rect(b, c, 0x206-b, d)   and   G_Rect(b, c+d, d, (0x1d7-c)-d)
// (FA reg plan: esi=b, edi=d, ebx=c scratch; verified against raw bytes).
// v1 was byte-identical except (a) ret 0x10 -> c2 10 00 needs __stdcall,
// (b) CL folded 0x1d7-c-d as (0x1d7-d)-c while FA does (0x1d7-c)-d — the
// r tmp pins the subtract order.
extern void __fastcall G_SetColor(long color);
extern void __stdcall G_Rect(long a, long b, long c, long d);
void __stdcall w44G_60240_q(int a, int b, int c, int d)
{
    long r;
    G_SetColor(a);
    G_Rect(b, c, 0x206 - b, d);
    r = 0x1d7 - c;
    G_Rect(b, c + d, d, r - d);
}