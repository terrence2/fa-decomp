// @MMReallocHandle@8 @ rva 0x35b90 (112 B) — probe v1.
#include <string.h>

typedef struct { char pad[8]; void *data; long size; unsigned short flags; } MMH;

extern void * __fastcall MMAllocHandle_q(unsigned long size, unsigned short flags); /* @MMAllocHandle@8 */
extern void __fastcall MMInternalFree_q(void *mem, unsigned long size); /* ?MMInternalFree@@YIDPAXK@Z */
extern void __fastcall MMFreeHandle_q(MMH *h); /* @MMFreeHandle@4 */

unsigned char __fastcall MMReallocHandle_q(MMH *h, unsigned long size)
{
    MMH *nd = MMAllocHandle_q(size, h->flags & 0xbfff);
    if (nd == 0)
        return 0;
    memcpy(nd->data, h->data, h->size < (long)size ? h->size : (long)size);
    MMInternalFree_q(h->data, (unsigned long)h->size);
    h->data = nd->data;
    h->size = nd->size;
    MMFreeHandle_q(nd);
    return 1;
}