// _SEQrun @ rva 0x46280 (16 B) — body is a bare c3 ret + census pad
// (8d642400+8d642400+8da42400000000).  FPO header reports params=8 but the
// body is empty — FA's own zero-body sequence runner.  Plain C empty void
// cdecl function, no maps, no calls.
void SEQrun(void)
{
}