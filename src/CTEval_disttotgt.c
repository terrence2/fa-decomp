// _CTEval_disttotgt @ rva 0x643e0 (23 B) — Dist(_curThing+0x11, tgt+0x11) >> 8
//   with the target base loaded from _serviceTicks+0xf4; the value+0x11 goes
//   into eax and pushes first (right-to-left), then the curThing offset (probe
//   d130; the 68 imm carries the DIR32 +0x11 addend baked).
extern char serviceTicks[];
extern char curThing[];
extern int __stdcall Dist(int a, int b);
int CTEval_disttotgt_q(void)
{
    return (Dist((int)(curThing + 0x11), *(long *)(serviceTicks + 0xf4) + 0x11) >> 8);
}
