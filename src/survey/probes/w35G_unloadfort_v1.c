/* w35G ?HARDUnloadFort@@YIDJJ@Z @ rva 0x51ef0 (112 B) v1 — w31C HardUnload twin
 * FA 96 B code, no tail pad. fastcall char(a,b):
 *   sub esp,4 / lea eax,[esp] / push esi / push edi / mov esi,edx
 *   / push 0 / push eax / push ecx / call ?HARDPtrsFort@@YGPAXJ...
 *   (stdcall; args right-to-left = a, &local, 0)
 *   / mov eax,[esp+8] (pv reload -> EAX) / test eax,eax / jne
 *   / xor al,al / pop edi / pop esi / add esp,4 / c3
 *   / mov edx,[esp+8] (pv 2nd reload -> EDX) / mov cx,[edx+4] (w)
 *   / add edx,4 (field ptr) / mov di,cx (mov di,cx!) / and edi,0x7fff
 *   / test esi,esi (b) / jne
 *   / xor edi,edi / mov al,1 / jmp merge
 *   / cmp edi,0x7fff / jne / mov al,1 / jmp merge
 *   / cmp edi,1 / jl / sub edi,esi / jns / xor edi,edi
 *   / mov al,1 / jmp merge
 *   / xor al,al
 *   merge: and cx,0x8000 / or cx,di / pop edi / 66 89 0a (mov [edx],cx)
 *   / pop esi / add esp,4 / c3
 */
extern void *__stdcall w35g_hpf(long, void **, void **);  /* ?HARDPtrsFort@@YGPAXJ... */

char __fastcall UnloadFort_q(long a, long b)
{
    void *pv;
    unsigned short *pt, w;
    unsigned long lim;
    char r;

    w35g_hpf(a, &pv, 0);
    if (pv == 0)
        return 0;
    pt = (unsigned short *)pv;
    w = pt[2];
    ++pt;
    lim = w;
    lim &= 0x7fff;
    if (b == 0) {
        lim = 0;
        r = 1;
    } else if (lim == 0x7fff) {
        r = 1;
    } else if ((long)lim < 1) {
        r = 0;
    } else {
        lim -= b;
        if ((long)lim < 0)
            lim = 0;
        r = 1;
    }
    *pt = (unsigned short)((w & 0x8000) | lim);
    return r;
}