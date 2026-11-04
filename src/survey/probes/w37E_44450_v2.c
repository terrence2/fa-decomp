/* w37E candidate 0x44450 (unnamed, cdecl, 1 param [esp+8] after push esi), 64 B + 6-B pad
   v2: byte-offset arithmetic via char* casts (v1's long* scaling was wrong). */
unsigned char w37e_44450(char *a1)
{
    long x = *(long *)(a1 + 0xe);
    if (x < 0xc8 || x > 0xd2) {
        *(long *)((char *)*(long **)a1 + 0x14) = 0x12;
        *(long *)((char *)*(long **)a1 + 0x18) = *(long *)(a1 + 0xe);
        (*(void (__cdecl **)(void *))(*(long **)a1))(a1);
    }
    return *(unsigned char *)((char *)*(long **)(a1 + 0x17e) + 0x11);
}