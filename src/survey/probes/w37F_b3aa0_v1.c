/* w37F v1 rva 0xb3aa0: zero fields of [esp+4] struct and of *(long*)(p+0x182) */
void w37f_b3aa0(char *p)
{
    int z;
    char *a;
    z = 0;
    a = (char *)(*(long volatile *)(p + 0x182));
    *(long *)(p + 0xba) = z;
    *(long *)(p + 0x72) = z;
    *(long *)(p + 0x16a) = z;
    *(a + 0x50) = (char)z;
    a = (char *)(*(long volatile *)(p + 0x182));
    *(a + 0x51) = (char)z;
    a = (char *)(*(long volatile *)(p + 0x182));
    *(long *)(a + 0x56) = z;
}