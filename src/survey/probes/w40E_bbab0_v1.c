/* rva 768688 (0xbbab0, 80 B, unnamed, 1 param, FPO esp): obj arg
 * [esp+0xc] post push esi/edi. edi = obj; x = *(long**)(obj+0x12)
 * (esi=8b 77 12); eax = x[5] ([esi+0x14]) file handle; ecx = x[6]
 * ([esi+0x18]) buffer; push eax; push 0x1000; push 1; push ecx;
 * call _fwrite; add esp,0x10 (cdecl); cmp eax,0x1000 (3d); je
 * success. FAILURE: eax=[edi] (vtable); push edi; mov [eax+0x14]
 * ,0x24 (c7 40 14 — vtable[5] is at +0x14, struct at vtable base??);
 * reload [edi]; call [eax] (ff 10, vtable[0], 1 arg); add esp,4;
 * falls through. SUCCESS: mov eax,[esi+0x18] (reLOAD x[6]); pop edi;
 * mov [esi],eax; mov al,1; mov [esi+4],0x1000 (c7 46 04); pop esi;
 * ret. */
extern long w40E_fwrite(void *, unsigned, unsigned, void *);

char __cdecl w40E_Fbuf(long o)
{
    long *x;
    long v;

    x = *(long **)(o + 0x12);
    if (w40E_fwrite((void *)x[6], 1, 0x1000, (void *)x[5]) != 0x1000) {
        v = *(long *)o;
        *(long *)((char *)v + 0x14) = 0x24;
        v = *(long *)o;
        ((void (__cdecl *)(long))((long *)v)[0])(o);
    }
    *(long *)x = x[6];
    *(long *)((char *)x + 4) = 0x1000;
    return 1;
}