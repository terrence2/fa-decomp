/* rva 100864 (0x18a00) 32 B FPO/esp gap chunk
 * mov eax,[esp+4]; mov edx,[eax+0x18e]; mov ecx,[eax+0x102];
 * mov [edx+0x5a],ecx; mov eax,[eax+0x56]; mov [edx+0x5e],eax; ret  (cdecl)
 * d (=[p+0x18e] target) reused for both stores; dst load first */
void __cdecl w31b_18a00(char *p)
{
    char *d = *(char **)(p + 0x18e);

    *(long *)(d + 0x5a) = *(long *)(p + 0x102);
    *(long *)(d + 0x5e) = *(long *)(p + 0x56);
}