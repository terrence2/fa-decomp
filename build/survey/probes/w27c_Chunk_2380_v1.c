// chunk @ rva 0x2380 (9088, unnamed 16 B) — mov eax,[esp+4] / xor ecx,ecx /
//   mov [eax+8],ecx / mov [eax+4],ecx / mov BYTE [eax+0x1a],cl / ret: zero a
//   dword pair + byte through one shared zero reg.
typedef struct {
    unsigned long pad;
    unsigned long f4;
    unsigned long f8;
    unsigned char rest[0x12];
    unsigned char b1a;
} W27Z;
void Chunk_2380_q(W27Z *p)
{
    p->f8 = 0;
    p->f4 = 0;
    p->b1a = 0;
}
