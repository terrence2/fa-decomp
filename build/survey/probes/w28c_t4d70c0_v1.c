// 0xd70c0 gap chunk (16 B) — v1
unsigned short __cdecl w28c_t4d70c0(char **pp)
{
    char *p;

    p = *pp;
    p += 4;
    *pp = p;
    return *(unsigned short *)(p - 4);
}
