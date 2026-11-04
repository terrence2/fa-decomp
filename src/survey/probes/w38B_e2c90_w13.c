/* w13 */
typedef struct { int a; int f; int b; } W38B_ACT;
extern volatile int _XcptActTabCountX;

W38B_ACT *w38b_e2c90(int id, W38B_ACT *p)
{
    W38B_ACT *p0 = p;
    W38B_ACT *q = p;
    unsigned int d, mask;
    for (;;) {
        if (q->f == id)
            break;
        q = q + 1;
        if (p0 + _XcptActTabCountX > q)
            continue;
        break;
    }
    d = q->f - id;
    mask = (d < 1) ? -1 : 0;
    return (W38B_ACT *)((int)q & (int)mask);
}