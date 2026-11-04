/* w42B 0x4b040 _ROGet@8 (128 B) v5 — w unsigned long (sib via EAX, xor/mov-ax
 * in-loop reload), w dead after the sib (return re-derefs *(ushort*)r), ct via
 * array-extern cast. */
extern char ro[];
extern void *objPtrs[];
extern unsigned short currentTime[];
extern unsigned long currentTicks[];
extern long w42b_uf4x;    /* -> ?SC_uf4@@3KA+0x4 */
extern char w42b_roEnd[]; /* -> _ro+0x6d6 */

unsigned short __stdcall ROGet(char *p, unsigned char flag)
{
    unsigned char *r;
    unsigned long w;

    if (*(short *)(p + 3) + 0xde > w42b_uf4x)
        return 0;
    r = (unsigned char *)ro;
    do {
        w = *(unsigned short *)r;
        if ((*(long *)((char *)objPtrs[w] + 1) & 1) == 0) {
            if (*(unsigned short *)(r + 6) <= *(unsigned short *)currentTime) {
                *(unsigned short *)(r + 6) = 0x7fff;
                *(char *)(r + 8) = flag;
                *(unsigned long *)(r + 2) = *(unsigned long *)currentTicks;
                return *(unsigned short *)r;
            }
        }
        r += 0xa;
    } while (r < (unsigned char *)w42b_roEnd);
    return 0;
}