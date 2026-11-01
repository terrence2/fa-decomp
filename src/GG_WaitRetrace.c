// @GG_WaitRetrace@0 @ rva 0x5da40 — ddInst->WaitForVerticalBlank(1) guarded by
//   a null test, shared single exit. Thiscall (push 1 + call, callee cleans) is
//   unreachable from C (fastcall puts 1 in edx, d42) → inline __asm (d69 exact).
extern void *ddInst;
extern void CDirDraw_WVB(void);

void GG_WaitRetrace_q(void)
{
    __asm {
        mov  ecx, ddInst
        test ecx, ecx
        jz   gwr_done
        push 1
        call CDirDraw_WVB
    gwr_done:
    }
}
