// _CTEval_tgtahead @ rva 0x64310 (48 B) — same word gate as tgtoffbeam and
//   AngleOffNose(target+0x11); then a pre-materialized bool from a signed
//   16-bit cmp: xor ecx,ecx / cmp ax,0x3ffc / setl cl / mov eax,ecx (wave-5
//   d50 shape on a (short) cast of the call result).
extern char serviceTicks[];
extern int __stdcall AngleOffNose(int a);
int CTEval_tgtahead_q(void)
{
    int r, b;
    if (*(short *)(serviceTicks + 0x20) == 0)
        return 0;
    r = AngleOffNose(*(long *)(serviceTicks + 0xf4) + 0x11);
    b = (short)r < 16380;
    return b;
}