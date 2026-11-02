// ?assignPacketCRC@@YAXAAUSERIAL_PACKET@@@Z @ rva 0x980a0 (48 B) —
//   crc = computePacketCRC(p) (eax); t = *(unsigned char*)p & 3 (mov
//   cl,[esi]/and ecx,3); p->[1] = al; if (t==0 || t==3) p->[0xa] = ah
//   (je over cmp ecx,3 / jne to the ah store — dup condition). FA writes
//   p->[1] via al and p->[0xa] via ah — plain C should reach both if the
//   crc stays in eax; fall to asm if CL resplits.
extern unsigned long computePacketCRC(void *p);

void __cdecl assignPacketCRC(void *p)
{
    unsigned long crc = computePacketCRC(p);
    unsigned long t = *(unsigned char *)p;
    t &= 3;
    ((unsigned char *)p)[1] = (unsigned char)crc;
    if (t == 0 || t == 3)
        ((unsigned char *)p)[0xa] = (unsigned char)(crc >> 8);
}