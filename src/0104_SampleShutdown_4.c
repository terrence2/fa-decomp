// @SampleShutdown@4 @ rva 0x122e0 — mov esi,ecx / mov ecx,[esi+0xc] / call
//   @MMFreePtr@4 / mov dword [esi+0xc],0 / pop esi / ret (probe v3).
extern void __fastcall MMFreePtr(void *h);

void __fastcall SampleShutdown(void *m)
{
    MMFreePtr(*(void **)((char *)m + 0xc));
    *(void **)((char *)m + 0xc) = 0;
}
