// ?SER_Initialize1@@YAJPAUCN_INFO@@J@Z @ rva 0x4bb90 (96 B; code 92 B +
// 4 B 8d 64 24 00 pad).  cdecl (CN_INFO *info, long arg2).  V2: zero held
// as a live local (FA keeps it in ECX; stores 89 0d, the 3b c1 compare
// partner), explicit-goto shape matching FA's branch polarity: jl bad /
// cmp 3 / jle ok / bad inline / ok last.
extern long w43H_mpOn1;      /* =?mpInfo@@3UMP_INFO@@C+0x154 */
extern long w43H_mpSt;       /* =?mpInfo@@3UMP_INFO@@C+0x170 */
extern long w43H_ctrlC1;     /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */
extern long w43H_ctrlC2;     /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x238 */
extern long (__cdecl *w43H_appIO)(long, char *); /* =?appIO@@3P6AJJPAD@ZA */
extern long w43H_opk14;      /* =?OutPacket@@3USERIAL_PACKET_WRAPPER@@A+0x14 */
extern long w43H_ipk14;      /* =?InPacket@@3USERIAL_PACKET_WRAPPER@@A+0x14 */
extern void __cdecl w43H_serIO(long n);  /* =_w43H_serIO@4=?serIO@@YAXJ@Z */

long __cdecl w43H_4bb90v2(void *info, long arg2)
{
    char *p = (char *)info;
    long zero = 0;
    long v;
    w43H_mpOn1 = zero;
    w43H_ctrlC1 = zero;
    w43H_appIO = *(long (__cdecl **)(long, char *))(p + 0xdac);
    w43H_opk14 = zero;
    w43H_ipk14 = 0x14;
    v = *(long *)(p + 0x64);
    if (v < zero)
        goto bad;
    if (v <= 3)
        goto ok;
bad:
    w43H_serIO(1);
    return 0;
ok:
    w43H_mpSt = *(long *)(p + 0x64);
    w43H_ctrlC2 = *(long *)(p + 0x64);
    return 2;
}