extern void *memcpy(void *, const void *, unsigned);

void jcopy_block_row(short *src, short *dst, unsigned n)
{
    memcpy(dst, src, n * 128);
}
