// v2: decl-order steering (stride before i, j before off), src address
//     spelled twice (FA reloads _items for memmove instead of CSE-ing).
extern long numItems;
extern void *items;
extern void *__fastcall MMAllocPtr(long size, unsigned long flags);
extern void *__cdecl memmove(void *dst, const void *src, unsigned count);

// v4: decl order [i,sum,stride]
char *__stdcall MakeNamesForList(void)
{
    char *p;
    long i, sum, stride, j, off, dst, len;

    sum = 0;
    stride = 0;
    i = 0;
    for (; i < numItems; i++) {
        sum += strlen((char *)items + stride + 0x11) + 1;
        stride += 0x30;
    }
    p = MMAllocPtr(sum + 1, 0x8000);
    j = 0;
    dst = 0;
    off = 0;
    for (; j < numItems; j++) {
        len = strlen((char *)items + off + 0x11) + 1;
        memmove(p + dst, (char *)items + off + 0x11, len);
        dst += len;
        off += 0x30;
    }
    p[dst] = 0;
    return p;
}
