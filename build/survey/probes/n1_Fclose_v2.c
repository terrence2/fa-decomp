// n1 Fclose: w23_Fclose_v1 spelling (rv=-1 first-decl). Patch plan:
// insert bf,-1; rewrite the mem byte-test to f6 46 0c 40; fix je disp;
// rewrite the EOF tail to FA's store/eax=edi form.
extern void __cdecl _lock_file(void *f);
extern int __cdecl _fclose_lk(void *f);
extern void __cdecl _unlock_file(void *f);

int __cdecl Fclose_r(void *f)
{
    int rv = -1;
    if (*(unsigned char *)((char *)f + 0xc) & 0x40) {
        *(unsigned long *)((char *)f + 0xc) = 0;
        return rv;
    }
    _lock_file(f);
    rv = _fclose_lk(f);
    _unlock_file(f);
    return rv;
}
