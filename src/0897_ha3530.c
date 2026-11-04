/* w36D_a3530_v1: (dst, src) gadget-copy stub @ 0xa3530 (48 B).
   FA: push esi edi / esi=[esp+0x10] (src) edi=[esp+0xc] (dst) /
   eax=[esi] ; [edi]=eax ; eax=[esi] (reload, store-clobbered) ; test eax je /
   lea ecx,[eax*4] / add esi,4 / shr ecx,2 / add edi,4 / rep movsd /
   pop edi esi ret. */
typedef unsigned long UL;
extern void *memcpy(void *, const void *, unsigned long);

void w36d_a3530(void *dst, void *src)
{
    *(UL *)dst = *(UL *)src;
    if (*(UL *)src)
        memcpy((((char *)dst) + 4), (((char *)src) + 4), *(UL *)src * 4);
}