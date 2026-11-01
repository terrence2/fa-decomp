// _line_overflow2 @ rva 0xbb6b0 (48 B) — line-division twin of
// _sphere_overflow: INT_DIVIDE_BY_ZERO (0xc0000094) / INT_OVERFLOW
// (0xc0000095) -> ContextRecord->Eip (+0xb8) = &_line_overflow_goes_here,
// return -1; else 0. Probe w13c_sph1 exact (identical shape, different
// store target — raw FA bytes checked: 0x4cdf14 imm32).
extern void line_overflow_goes_here(void);

int __cdecl line_overflow2(long *ep)
{
    long code = *(long *)*(long **)ep;
    if (code == 0xc0000094 || code == 0xc0000095) {
        void *ctx = *(void **)((char *)ep + 4);
        *(long *)((char *)ctx + 0xb8) = (long)line_overflow_goes_here;
        return -1;
    }
    return 0;
}