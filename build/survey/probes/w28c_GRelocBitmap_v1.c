// 0xb3cd0 @G_RelocBitmap@8 — v1: fastcall self(ecx)/rel(edx)
void __fastcall w28c_GRelocBitmapQ(char *s, long rel)
{
    long p, p3, c2, c3, o;
    char *q;

    if ((p = *(long *)(s + 0xa)) != 0) { *(long *)(s + 0xa) = p + rel; }
    if ((p = *(long *)(s + 0x12)) != 0) { *(long *)(s + 0x12) = p + rel; }
    if ((p = *(long *)(s + 0x1a)) != 0) {
        p += rel;
        *(long *)(s + 0x1a) = p;
        q = (char *)p;
        while (*(short *)q != -1) {
            *(long *)(q + 0x6) += rel;
            q += 0xa;
        }
    }
    p3 = *(long *)(s + 0x22);
    o = 0;
    c2 = 0;
    if (p3 != 0) {
        p3 += rel;
        c3 = *(long *)(s + 0x6);
        *(long *)(s + 0x22) = p3;
        if (c3 > 0) {
            do {
                q = (char *)(*(long *)(s + 0x22));
                o += 4;
                c2++;
                *(long *)(q + o - 4) += rel;
            } while (c2 < c3);
        }
    }
    if ((p = *(long *)(s + 0x2a)) != 0) { *(long *)(s + 0x2a) = p + rel; }
}
