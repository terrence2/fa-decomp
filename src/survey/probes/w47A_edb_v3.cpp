/* rva 352496 v3: v_int-shaped staged gradients + inline pd/pu pointers */
typedef struct {
    unsigned char _p[0x18];
    unsigned char tbl[0x300];
} FrameHeader;

typedef struct {
    unsigned char _p[0xc1b0];
    unsigned int f1b0;
} GlobalData;

void EDB(unsigned char *bits, unsigned char *dst, FrameHeader *fh, GlobalData *gd)
{
    unsigned char *tp = fh->tbl;
    unsigned short f0, upd, cur, cur2, c2, cnt;
    int a0, a1, a2, b0, b1, b2;
    int gU, gD;
    unsigned char *pd, *pu;

    f0 = (gd->f1b0 & 1) << 7;
    cnt = 0x200;
    do {
        cur = *bits++;
        if (cur == 0 || cur == 0x80) {
            gU = 0x0fffffff;
        } else {
            pd = tp + 3 * (cur - f0);
            pu = tp + 3 * ((cur - 1) - f0);
            a0 = pd[0]; a1 = pd[1]; a2 = pd[2];
            b0 = pu[0]; b1 = pu[1]; b2 = pu[2];
            gU = (a0-b0)*(a0-b0) + (a1-b1)*(a1-b1) + (a2-b2)*(a2-b2);
        }
        if (cur == 0x7f || cur == 0xff) {
            gD = 0x0fffffff;
        } else {
            pd = tp + 3 * (cur - f0);
            pu = tp + 3 * ((cur + 1) - f0);
            a0 = pd[0]; a1 = pd[1]; a2 = pd[2];
            b0 = pu[0]; b1 = pu[1]; b2 = pu[2];
            gD = (a0-b0)*(a0-b0) + (a1-b1)*(a1-b1) + (a2-b2)*(a2-b2);
        }
        if (gU > 8)
            gU = 0x0fffffff;
        if (gD > 8)
            gD = 0x0fffffff;
        if (gD > gU)
            upd = cur - 1;
        else if (gD < gU)
            upd = cur + 1;
        else if (gU == 0x0fffffff)
            upd = cur;
        else
            upd = cur - 1;

        cur2 = *bits++;
        if (cur2 == 0 || cur2 == 0x80) {
            gU = 0x0fffffff;
        } else {
            pd = tp + 3 * (cur2 - f0);
            pu = tp + 3 * ((cur2 - 1) - f0);
            a0 = pd[0]; a1 = pd[1]; a2 = pd[2];
            b0 = pu[0]; b1 = pu[1]; b2 = pu[2];
            gU = (a0-b0)*(a0-b0) + (a1-b1)*(a1-b1) + (a2-b2)*(a2-b2);
        }
        if (cur2 == 0x7f || cur2 == 0xff) {
            gD = 0x0fffffff;
        } else {
            pd = tp + 3 * (cur2 - f0);
            pu = tp + 3 * ((cur2 + 1) - f0);
            a0 = pd[0]; a1 = pd[1]; a2 = pd[2];
            b0 = pu[0]; b1 = pu[1]; b2 = pu[2];
            gD = (a0-b0)*(a0-b0) + (a1-b1)*(a1-b1) + (a2-b2)*(a2-b2);
        }
        if (gU > 8)
            gU = 0x0fffffff;
        if (gD > 8)
            gD = 0x0fffffff;
        if (gD > gU)
            c2 = cur2 - 1;
        else if (gD < gU)
            c2 = cur2 + 1;
        else if (gU == 0x0fffffff)
            c2 = cur2;
        else
            c2 = cur2 - 1;

        dst[0] = cur;
        dst[1] = upd;
        dst[2] = cur2;
        dst[3] = c2;
        dst[4] = upd;
        dst[5] = cur;
        dst[6] = c2;
        dst[7] = cur2;
        dst += 8;
    } while (--cnt);
}
