// ?SER_ProcessStatusPacket@@YAXAAUSERIAL_PACKET_WRAPPER@@@Z v3 — the block
// condition is m != -1 (FA: 74 21 je skips the block when m == -1; v2 gave
// 75 21 jne because the C said m == -1).
extern void __cdecl w43b_uqh(void *q, long n);
extern long w43b_InQ;      /* _w43b_InQ=?InQueue@@3USERIAL_QUEUE@@A */
extern long w43b_mpe;      /* _w43b_mpe=?mpInfo@@3UMP_INFO@@C+0x164 */
extern long w43b_mpeX;     /* twin of the same address, anti-CSE */
extern char w43b_ctrl128;  /* _w43b_ctrl128=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x128 */
extern char w43b_mpeA[];   /* _w43b_mpeA=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x18e */
extern char w43b_ctrl12a;  /* _w43b_ctrl12a=?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12a */

typedef struct { unsigned char pad[0x20]; unsigned char f20;
                 unsigned char f21; unsigned char f22;
                 unsigned char f23; } W43_SPW;

void __cdecl w43b_spsp(W43_SPW *p)
{
    long m;
    long m2;

    w43b_uqh(&w43b_InQ, *(unsigned long *)((char *)p + 4) + 1);
    m = w43b_mpe;
    w43b_ctrl128 = 0;
    if (m != -1) {
        m2 = w43b_mpeX;
        w43b_mpeA[m2 ^ 1] = p->f20;
        if (p->f23 != (long)(m2 ^ 1))
            w43b_ctrl12a = 1;
    }
    if (p->f21)
        w43b_ctrl12a = 1;
}