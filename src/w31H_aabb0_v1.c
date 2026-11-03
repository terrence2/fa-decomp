/* w31H_aabb0 v1: FA bytes (rva 0xaabb0, 21 B code + 11 B pad): mov eax,[esp+4];
   mov ecx,[eax+0x18e]; mov BYTE PTR [ecx+0x22],0; mov edx,[eax+0x56];
   mov [ecx+0x28],edx; ret. cdecl, 1 param. */
void w31h_4aabb0(void *p)
{
    char *c = *(char **)((char *)p + 0x18e);
    c[0x22] = 0;
    *(long *)(c + 0x28) = *(long *)((char *)p + 0x56);
}