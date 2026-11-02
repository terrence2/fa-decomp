// _line_overflow1 @ rva 0xbb660 (80 B, FPO fpo/esp params=1) — SEH
// exception filter for the integer line-overflow site: matches
// C0000094 (integer div-by-zero) / C0000095 (integer overflow); hit
// swaps the two dwords at +0x9c/+0xa4 of the exception context record
// pointee ([ep+4], the classic FA swap-pair) and stores the restart
// address at +0x2e*4 (+0xb8) as a c7 80 mem-imm32 with DIR32 (dis.py
// elided it — literal-VA trap rule: the & of the mapped symbol
// _lineOverflowHere=?,_line_overflow_goes_here reproduces FA's fixup)
// then returns -1 (EXCEPTION_EXECUTE_HANDLER); 0 otherwise. Plain C:
// **ep deref once into a named int code, || guard, named t/u swap
// temps — CL 10.20 emits FA's eax/edx/ecx plan (no push ebx, direct
// c7 80 store) from this spell.
extern int lineOverflowHere;

int line_overflow1(void *ep)
{
    int code = **(int **)ep;
    if (code == 0xc0000094 || code == 0xc0000095) {
        long *ctx = *(long **)((char *)ep + 4);
        long t = ctx[0x29];
        long u = ctx[0x27];
        ctx[0x29] = u;
        ctx[0x27] = t;
        ctx[0x2e] = (long)&lineOverflowHere;
        return -1;
    }
    return 0;
}