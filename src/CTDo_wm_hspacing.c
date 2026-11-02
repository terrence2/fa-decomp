// _CTDo_wm_hspacing @ rva 0x658c0 (80 B) — FA asm: 56 (push esi)/e8
//   $FA$_t_464c90 (clamp call, v -> eax)/3d 00 02 00 00 (cmp eax,0x200)/
//   8b f0 (mov esi,eax)/7d 05 (jge)/be 00 02 00 00 (mov esi,0x200)/
//   81 fe 20 4e 00 00 (cmp esi,0x4e20)/7e 05 (jle)/be 20 4e 00 00
//   (mov esi,0x4e20)/a0 <_serviceTicks+0xec>/84 c0/75 0x1b (jne exit)/
//   66 a1 <_curId>/6a 00/6a 00/50/e8 _WNGPart@12/3c 01 (cmp al,1)/
//   75 07 (jne exit)/8b ce (mov ecx,esi)/e8 $FA$_t_45e1a0 (fastcall
//   apply)/5e/c3.  Clamps the tick-check value into [0x200,0x4e20], skips
//   the game-pause gate, then applies the clamp as the fastcall arg when
//   WNGPart(curId,0,0) == 1.  CTDo_wm_formation/ CTDo_wm_control twin
//   (wave-17): plain C holds the clamp two-if form and the mid-function
//   fastcall call.  Probe build/w4probe/b20f_CTDo_wm_hspacing.obj — exact modulo
//   fixup dwords.
extern char serviceTicks[];
extern unsigned short curId;

extern long __stdcall ctTickCheck(void);
extern char __stdcall WNGPart(short a, int b, int c);
extern void __fastcall ctHsSp(int v);

void CTDo_wm_hspacing_q(void)
{
    long v = ctTickCheck();
    if (v < 0x200)
        v = 0x200;
    if (v > 0x4e20)
        v = 0x4e20;
    if (serviceTicks[0xec])
        return;
    if (WNGPart(curId, 0, 0) == 1)
        ctHsSp((int)v);
}