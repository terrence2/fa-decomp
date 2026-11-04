/* w34E_903b0 @ rva 0x903b0 (48 B) — cdecl: t = p->[0x16e]; if (uchar
 * [p+0x42]) call *(void(**)(void*))([p+0x196]+8) with arg p; then
 * ++*(unsigned long*)(t+0xa).  FA: mov eax,[esp+4] / push esi / mov
 * esi,[eax+0x16e] / mov cl,[eax+0x42] / test / push eax / mov
 * eax,[eax+0x196] / call [eax+8] / add esp,4 / inc [esi+0xa]. */
typedef void (__cdecl *w34E_fp)(void *);

void __cdecl w34E_903b0(void *p)
{
    void *t;
    void *ft;
    t = *(void **)((char *)p + 0x16e);
    if (*(unsigned char *)((char *)p + 0x42)) {
        ft = *(void **)((char *)p + 0x196);
        (*(w34E_fp *)((char *)ft + 8))(p);
    }
    ++*(unsigned long *)((char *)t + 0xa);
}