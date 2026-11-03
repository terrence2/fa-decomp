typedef struct { unsigned long type; } CN_INFO;

long __cdecl w32f_cfigchk(CN_INFO *p)
{
    unsigned long n;
    unsigned long crc;
    n = 0;
    crc = 0;
    switch (p->type) {
    case 3: n = 0xddc; break;
    case 2: n = 0xdd8; break;
    case 1: n = 0xdb0; break;
    default: return 1;
    }
    while (n) {
        unsigned long t;
        unsigned long b;
        t = (crc >> 24) & 0xff;
        b = *(unsigned char *)p;
        p = (CN_INFO *)((char *)p + 1);
        crc = (crc << 8) ^ t ^ b;
        n--;
    }
    return (long)crc;
}