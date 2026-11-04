// _sphere_overflow @ rva 0xbb5c0 (48 B) — EXCEPTION filter for the sphere
// math: if ExceptionCode is INT_DIVIDE_BY_ZERO (0xc0000094) or INT_OVERFLOW
// (0xc0000095), repoint ContextRecord->Eip (+0xb8) at the FA code chunk
// `_sphere_out` and return -1 (EXCEPTION_CONTINUE_EXECUTION); else 0. The
// c7 80 [ctx+0xb8] imm32 store is a DIR32-relocated function address (probe
// w13c_sph1 exact; dis.py elides the store line — raw FA bytes checked).
extern void sphere_out(void);

int __cdecl sphere_overflow(long *ep)
{
    long code = *(long *)*(long **)ep;
    if (code == 0xc0000094 || code == 0xc0000095) {
        void *ctx = *(void **)((char *)ep + 4);
        *(long *)((char *)ctx + 0xb8) = (long)sphere_out;
        return -1;
    }
    return 0;
}