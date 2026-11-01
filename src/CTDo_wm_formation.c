// _CTDo_wm_formation @ rva 0x65960 (64 B) — FA asm: e8 $FA$_t_464c90 (clamp
//   call)/85 c0/7d .. / 33 c0/eb .. / 83 f8 02/7f .. / b8 02 00 00 00 (clamp
//   0..2)/8a 0d <_serviceTicks+0xec>/84 c9/75 .. /33 c9/8a 0d <curThing+
//   0xfc>/3b c8/74 .. /8b c8/e9 $FA$_t_45e160 (fastcall tail; ret on match
//   or serviceTicks gate).  Plain C wins including the fastcall tail-jmp.
//   Probe build/w4probe/b17_ctdowm_v1.c — exact modulo fixup dwords.

extern char serviceTicks[];
extern char curThing[];

extern long __cdecl ctTickCheck(void);
extern void __fastcall ctWmApply(int v);

void CTDo_wm_formation(void) {
    long v = ctTickCheck();
    if (v < 0)
        v = 0;
    else if (v > 2)
        v = 2;
    if (serviceTicks[0xec])
        return;
    if ((unsigned char)curThing[0xfc] == v)
        return;
    ctWmApply((int)v);
}