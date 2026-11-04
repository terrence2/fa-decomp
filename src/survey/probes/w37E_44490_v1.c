/* w37E candidate 0x44490 : twin of 0x44450 with bounds 0xca..0xd2 and byte
   offset 0x10 in the return byte. */
unsigned char w37e_44490(char *a1)
{
    long x = *(long *)(a1 + 0xe);
    if (x < 0xca || x > 0xd2) {
        *(long *)((char *)*(long **)a1 + 0x14) = 0x12;
        *(long *)((char *)*(long **)a1 + 0x18) = *(long *)(a1 + 0xe);
        (*(void (__cdecl **)(void *))(*(long **)a1))(a1);
    }
    return *(unsigned char *)((char *)*(long **)(a1 + 0x17e) + 0x10);
}