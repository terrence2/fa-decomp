/* rva 125488 v2: fix pointer+pointer add; p as char*, h loaded, h+(long)p */
int __stdcall w31b_1ea30_v2(char *p)
{
    char *h = *(char **)(p + 0x3c);

    return *(long *)(h + (long)p) == 0x4c50;
}