/* w42A_cdi_v1.c — FA chunk ?COLDrawInfo@@YGXGF@Z rva 0x2dc70 (VA 0x42dc70)
 * stdcall void(ushort col, short num), NO in-image callers:
 *   push ebx/esi/edi/ebp; mov bp,[esp+0x14]; mov eax,ebp; and eax,0xffff;
 *   mov ecx,[0x54ad98+eax*4] (=objPtrs, sib disp+eax*4); mov edx,[ecx+5];
 *   push edx; call _COLGetInfo@4 (identity, converted);
 *   mov si,[esp+0x18]; mov ebx,eax; test si,si; jge; block1: lea eax,[ebx+4];
 *   push; push 0xf; push ebp(raw); call $FA$_t_42dcf0 (cdecl q); add esp,0xc;
 *   al=[ebx+0x10]; add ebx,0x10; xor edi,edi; test al,0x80; je out;
 *   loop top =test si,si; jl in; movsx eax,si; cmp eax,edi; jne next;
 *   in: lea eax,[ebx+2]; push; al=[ebx+1] overwrites lea result al;
 *   and eax,0xffff00ff; push; push ebp; call $FA$_t_42dcf0; add esp,0xc;
 *   next: al=[ebx+0xe]; add ebx,0xe; inc edi; test al,0x80; jne loop;
 *   pop ebp/edi/esi/ebx; ret 8. pad 0500000000 (5 B).
 */
extern char *objPtrs[];
extern long __stdcall COLGetInfo(long id);
extern void __cdecl w42A_q(unsigned short flag, long color, void *arg);

void __stdcall w42A_cdi(unsigned short col, short num)
{
    char *rec;
    char *r;
    char *p2;
    unsigned char c;
    long e;
    long i;

    rec = objPtrs[col];
    r = (char *)COLGetInfo(*(long *)(rec + 5));
    if (num < 0) {
        w42A_q(col, 0xf, r + 4);
    }
    p2 = r;
    c = *(unsigned char *)(p2 + 0x10);
    p2 += 0x10;
    i = 0;
    if (c & 0x80) {
        do {
            if (num < 0 || num == i) {
                e = (long)(p2 + 2);
                w42A_q(col, (e & 0xffff0000) | *(unsigned char *)(p2 + 1),
                       (char *)e);
            }
            c = *(unsigned char *)(p2 + 0xe);
            p2 += 0xe;
            i++;
        } while (c & 0x80);
    }
}