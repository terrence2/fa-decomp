/* rva 0x74f60 (dec 479072), 80 B ?jcopy_sample_rows@@YAXPAPAEH0HHI@Z.
 * v2: sp-advance before dp-advance (FA: add edx then add ebx), counter as
 * a plain local n = nrows, dp declared after sp (FA: dp lands in ebx).
 */
extern void *memcpy(void *, const void *, unsigned int);

void jcopy_sample_rows0(unsigned char **srcs, int srcIdx, unsigned char **dsts,
                        int dstIdx, int nrows, unsigned long width)
{
    unsigned char **sp = srcs + srcIdx;
    unsigned char **dp = dsts + dstIdx;
    int n = nrows;

    for (; n > 0; n--) {
        unsigned char *s = *sp;
        unsigned char *d = *dp;
        ++sp;
        ++dp;
        memcpy(d, s, width);
    }
}