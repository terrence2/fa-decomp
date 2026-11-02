// chunk @ rva 0x2380 (9088, unnamed 16 B) — v2: b1a at 0x1a (rest[0xe]).
typedef struct {
    unsigned long pad;
    unsigned long f4;
    unsigned long f8;
    unsigned char rest[0xe];
    unsigned char b1a;
} W27Z;
void Chunk_2380_q(W27Z *p)
{
    p->f8 = 0;
    p->f4 = 0;
    p->b1a = 0;
}
