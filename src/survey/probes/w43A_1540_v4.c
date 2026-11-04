/* rva 0x1540 (58 B) - build first-fit decode entries; FA loads args 3/4/5 */
void w43A_1540(long n, long spare, unsigned char *len, unsigned char *code, unsigned char *dst)
{
    unsigned long m, v;
    long i;

    for (i = n - 1; i >= 0; i--) {
        m = 1U << len[i];
        v = code[i];
        do {
            dst[v] = (unsigned char)i;
            v += m;
        } while (v < 0x100);
    }
}
