// _WNGInit@0 @ rva 0x5da90 (383632, 36 B code + 12 B pad) — FA asm:
//   bf <wingIds>/b9 32/f3 ab (memset 0xc8 via 50 dwords)/a3 <wingSizes>/
//   66 a3 <wingSizes+8> (word store, ws[4]=0)/5f (pop edi — DEFERRED past
//   all the stores)/5e/a3 <...>/c3 shape per probe v1 fit — the twin of
//   GRPInit. EXACT as plain C + 2 patches (survey tier-1): constant-size
//   memset inlines to rep stosd (a3 + 66-a3 word twin stores), CL emits
//   the early pop edi and streams the word store as 66 a3 <moffs>
//   (6 B + d32) where FA keeps ecx = wingSizes and uses 66 89 41 08
//   (reg+disp8) with the pop deferred to the end.
//   patch 0xf: delete CL's early 5f (pop edi) — root-caused: FA pops edi
//     only at the tail, after the word store; CL pops right after stosd.
//   patch 0x19: replace CL[0x19,0x20) (66 a3 <wingSizes+8> 6 B + c3 +
//     leftover, 7 B) with FA's 11 B b9 <wingSizes>/5f/66 89 41 08/c3,
//     attaching DIR32 at site 1 (the b9 imm32 d32).
//
// probes: build/survey/probes/t1_wnginit_v1.c (EXACT via patch), _v2.c (no)
//   — run: python3 tools/fitobj.py build/survey/probes/t1_wnginit_v1.obj
//   383632 --patch '0xf,1,' --patch '0x19,7,b9000000005f66894108c3,1:6:_wingSizes'
//
// maps VERBATIM: [] (wingIds/wingSizes resolve identity)
// entry: add "patch": ["0xf,1,", "0x19,7,b9000000005f66894108c3,1:6:_wingSizes"]
#include <string.h>
extern char wingIds[];
extern long wingSizes[];

void WNGInit_q(void)
{
    memset(wingIds, 0, 0xc8);
    wingSizes[0] = 0;
    wingSizes[1] = 0;
    {
        short *ws = (short *)wingSizes;
        ws[4] = 0;
    }
}