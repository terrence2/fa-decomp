/* w42A_seek_v1.c — FA chunk $FA$_t_421cd0 rva 0x21cd0 (VA 0x4021cd0)
 * stdcall ret 0xc, NO prolog/frame: mov eax,[esp+4];
 *   test byte[eax],1; jne; do {cl=[eax-0x44]; sub eax,0x44; test cl,1; je};
 *   ecx=[esp+8]; test; je; [ecx]=eax; xor ecx,ecx; cl=[eax]; test cl,2;
 *   jne; do {cl=[eax+0x44]; add eax,0x44; inc ecx; test cl,2; je};
 *   eax=[esp+0xc]; test; je; [eax]=ecx; ret 0xc. No pad.
 * Callers still stub -> alias 0=$FA$_t_421cd0.
 */
void __stdcall w42A_seek(char *q, long *o1, long *o2)
{
    unsigned char c;
    long n;

    if (!(*q & 1)) {
        do {
            c = *(q - 0x44);
            q -= 0x44;
        } while (!(c & 1));
    }
    if (o1)
        *o1 = (long)q;
    n = 0;
    c = *q;
    if (!(c & 2)) {
        do {
            c = *(q + 0x44);
            q += 0x44;
            n++;
        } while (!(c & 2));
    }
    if (o2)
        *o2 = n;
}