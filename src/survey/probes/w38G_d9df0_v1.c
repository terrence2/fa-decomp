/* w38G (unnamed) @ 0xd9df0 (44 B) — v1: CRT _initmbctable-ish zeroing.
 * FA: push edi; xor eax,eax; rep stosd (edi=__mbctype, ecx=0x40) + stosb;
 * then five dword stores (a3 mov ds:0x51a7b8; mov ecx,0x51a7b8; pop edi
 * interleave; mov ds:0x51a7ac; mov ds:0x51a7b0; [ecx+4]; [ecx+8]); ret. */
extern char w38g_mbc[];                       /* -> __mbctype (0x51a6a8) */

void w38g_d9df0(void)
{
    unsigned char *p;
    unsigned long *q;
    unsigned long zero;
    int i;

    zero = 0;
    p = w38g_mbc;
    for (i = 0; i < 0x101; i++)
        p[i] = 0;
    *(unsigned long *)(w38g_mbc + 0x110) = zero;
    q = (unsigned long *)(w38g_mbc + 0x110);
    *(unsigned long *)(w38g_mbc + 0x104) = zero;
    *(unsigned long *)(w38g_mbc + 0x108) = zero;
    *(q + 1) = zero;
    *(q + 2) = zero;
}