/* ?computePacketCRC@@YAKAAUSERIAL_PACKET@@@Z @ rva 0x97fc0 (112 B) -- v2.
 * v1 materialized the type-test bool in EDI (bf imm32); FA keeps it in BL
 * (b3 00/b3 01, 84 db tests). Fix: b is an unsigned char local. The tail in
 * FA reads as two separate ifs sharing the single epilogue:
 *   if (b) p->fA = sa;  if (!b) crc &= 0xff;  return crc; */
extern unsigned long __stdcall CdrvCrc16(unsigned long n, void* p);

typedef struct {
    unsigned char f0;
    unsigned char f1;
    unsigned char p2[8];
    unsigned char fA;
    unsigned char pad[0x14];
} W37H_SP;

unsigned long computePacketCRC(W37H_SP* p)
{
    unsigned char s1, sa, b;
    unsigned long v, crc;
    v = p->f0 & 3;
    b = (v == 0) || (v == 3);
    s1 = p->f1;
    sa = p->fA;
    p->f1 = 0xff;
    if (b)
        p->fA = 0xff;
    crc = CdrvCrc16(0x18, p) & 0xffff;
    p->f1 = s1;
    if (b)
        p->fA = sa;
    if (!b)
        crc &= 0xff;
    return crc;
}