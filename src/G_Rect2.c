// _G_Rect2@16 @ rva 0x95e10 (48 B) — FA asm (stdcall, FPO frame): 8b 44 24 0c
//   /2b 44 24 04 (mov eax,[x2]-[x])/40 (inc)/50 ... converts the
//   (x,y,x2,y2) inclusive-corner pair into the G_Rect (x,y,w,h) form and
//   tail-calls _G_Rect@16 (FF 25 imp thunk tail via the stdcall last-call
//   rule).  G_URect2 twin.  Plain C exact — CL 4.2 emits the same two
//   sub/inc width-height computations and the tail-call (probe
//   build/w4probe/b20b_gr2_v1.obj — exact).
extern void __stdcall G_Rect(long x, long y, long w, long h);

void __stdcall G_Rect2(long x, long y, long x2, long y2)
{
    G_Rect(x, y, x2 - x + 1, y2 - y + 1);
}