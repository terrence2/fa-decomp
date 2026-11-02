/* @DialogGetString@4 @ 0x877c0 (112B)
   FA switch: q = @DialogGetPtr@4(ecx); tw = word[q] & 0x7fff (32-bit ops on
   the 16-bit read: mov cx,[eax]; and ecx,0x7fff); je arm0; cmp ecx,2 je arm2;
   cmp ecx,4 je arm4; default = xor eax,eax; pop esi; pop ebx; ret INLINE,
   arm bodies AFTER. case0 = eax=[q+0x1a]; case2 = eax=[q+0x14]; case4 =
   w=word[q+0x1a] in cx; d=[q+0x20] in edx; n=word[q+0x24] in si;
   test si,0x8000: je loop; else movsx ecx,cx; and esi,0x7fff (81 e6!);
   call @PageText?@8 (arg1=w in ecx, d stays edx); lea edx,[esi+eax] = POINTER
   ADD (the return). loop: test cx,cx; je end; body = mov bl,[edx]; mov eax,edx
   (dead r store); inc edx; test bl,bl; jne body; dec cx; jne body; 
   end: mov eax,edx; pop esi; pop ebx; ret. */
extern unsigned char *__fastcall DialogGetPtr_q(unsigned long p);  /* @DialogGetPtr@4 */
extern char *__fastcall PageText_q(long w, unsigned long d);       /* ?PageText@@YIPADJ@Z */

unsigned char *__fastcall DialogGetString_q(unsigned long p)
{
    unsigned char *q;
    unsigned long tw;
    short w;
    unsigned char *d;
    unsigned short n;
    unsigned char *r;

    q = DialogGetPtr_q(p);
    tw = *(unsigned short *)q & 0x7fff;
    switch (tw) {
    case 0:
        return (unsigned char *)(*(unsigned long *)(q + 0x1a));
    case 2:
        return (unsigned char *)(*(unsigned long *)(q + 0x14));
    case 4:
        w = *(short *)(q + 0x1a);
        d = *(unsigned char **)(q + 0x20);
        n = *(unsigned short *)(q + 0x24);
        if (n & 0x8000)
            return (unsigned char *)(PageText_q(w, d) + (n & 0x7fff));
        while (w != 0) {
            do {
                r = d;
            } while (*d++);
            w--;
        }
        return d;
    }
    return 0;
}
