void *__fastcall w32f_zthis(void *p)
{
    long z;
    z = 0;
    *(long *)((char *)p + 8) = 0x6c;
    *(long *)p = z;
    *(long *)((char *)p + 0x80) = z;
    *(long *)((char *)p + 4) = z;
    *(long *)((char *)p + 0x74) = z;
    *(char *)((char *)p + 0xf4) = (char)0;
    *(long *)((char *)p + 0x78) = z;
    *(long *)((char *)p + 0x7c) = z;
    *(long *)((char *)p + 0xf0) = z;
    return p;
}