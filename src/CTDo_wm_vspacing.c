// _CTDo_wm_vspacing @ rva 0x65910 (80 B) — byte-twin of _CTDo_wm_hspacing
//   against the vertical-spacing apply chunk: FA asm identical through the
//   WNGPart gate, tail call is e8 $FA$_t_45e1e0 (own fastcall apply, so
//   keep a distinct extern).  Plain C; clamp [0x200,0x4e20] two-if form.
//   Probe build/w4probe/b20f_CTDo_wm_vspacing.obj — exact modulo fixup dwords.
extern char serviceTicks[];
extern unsigned short curId;

extern long __stdcall ctTickCheck(void);
extern char __stdcall WNGPart(short a, int b, int c);
extern void __fastcall ctVsSp(int v);

void CTDo_wm_vspacing_q(void)
{
    long v = ctTickCheck();
    if (v < 0x200)
        v = 0x200;
    if (v > 0x4e20)
        v = 0x4e20;
    if (serviceTicks[0xec])
        return;
    if (WNGPart(curId, 0, 0) == 1)
        ctVsSp((int)v);
}