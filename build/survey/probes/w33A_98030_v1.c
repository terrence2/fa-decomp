typedef struct USERIAL_PACKET {
    unsigned char data[16];
} USERIAL_PACKET;

int packetCRC_q(USERIAL_PACKET *p)
{
    switch (p->data[0] & 3) {
    case 0:
    case 3:
        return (p->data[10] << 8) | p->data[1];
    case 1:
    case 2:
        return p->data[1];
    }
    return 0;
}