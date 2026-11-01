// _CTDo_wm_control @ rva 0x659a0 (64 B) — twin of CTDo_wm_formation: FA asm
//   e8 $FA$_t_464c90/85 c0/7d .. /33 c0/eb .. /83 f8 04/7c 05/b8 03 00 00 00
//   (clamp: >=4 -> 3, so the jl polarity is v>=4 sets 3)/8a 0d <_serviceTicks
//   +0xec>/84 c9/75 .. /33 c9/8a 0d <curThing+0xfb>/3b c8/74 .. /8b c8/
//   e9 $FA$_t_45e160.  Plain C; note "if (v >= 4) v = 3;" (NOT v > 4) to
//   keep FA's 7c 05 jl-over-store polarity.
//   Probe build/w4probe/b17_ctdowc_v1.c — exact modulo fixup dwords.

extern char serviceTicks[];
extern char curThing[];

extern long __cdecl ctTickCheck(void);
extern void __fastcall ctWmApply(int v);

void CTDo_wm_control(void) {
    long v = ctTickCheck();
    if (v < 0)
        v = 0;
    else if (v >= 4)
        v = 3;
    if (serviceTicks[0xec])
        return;
    if ((unsigned char)curThing[0xfb] == v)
        return;
    ctWmApply((int)v);
}