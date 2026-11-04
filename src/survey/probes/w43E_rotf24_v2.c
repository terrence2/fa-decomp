/* FA 0x412740 _GetRotatedOffsetF24@12 (96 B) v2: buf[5], named t-locals for reg loads */
struct F24P3 { long d0; long d1; long d2; };
extern void __stdcall MakeViewRotationMatrix(unsigned long *buf,
    unsigned short w1, unsigned short w2, unsigned short w3); /* _MakeViewRotationMatrix@16 */
extern void __stdcall MultF24PointByMatrix(struct F24P3 *p, unsigned long *buf); /* _MultF24PointByMatrix@8 */

void __stdcall w43E_GetRotatedOffsetF24(const struct F24P3 *v, const unsigned char *m, struct F24P3 *out)
{
    unsigned long buf[5];
    long t0, t1, t2;

    t0 = *(long *)(m + 0x11);
    t1 = *(long *)(m + 0x15);
    t2 = *(long *)(m + 0x19);
    out->d0 = v->d0 - t0;
    out->d1 = v->d1 - t1;
    out->d2 = v->d2 - t2;
    MakeViewRotationMatrix(buf, *(unsigned short *)(m + 0x1d),
        *(unsigned short *)(m + 0x1f), *(unsigned short *)(m + 0x21));
    MultF24PointByMatrix(out, buf);
}