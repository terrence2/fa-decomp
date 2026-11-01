// _CTEval_tgtoffbeam @ rva 0x642e0 (48 B) — word gate at _serviceTicks+0x20,
//   AngleOffNose(target+0x11) pushed from _serviceTicks+0xf4, then / 0xb6 via
//   the 16-bit idiv pair (mov cx,0xb6 / cwd / idiv cx): the int call result
//   is truncated implicitly by cwd's AX read (wave-5 d53 shape).
extern char serviceTicks[];
extern int __stdcall AngleOffNose(int a);
int CTEval_tgtoffbeam_q(void)
{
    short q = 0xb6;
    if (*(short *)(serviceTicks + 0x20) == 0)
        return 0;
    return (short)AngleOffNose(*(long *)(serviceTicks + 0xf4) + 0x11) / q;
}