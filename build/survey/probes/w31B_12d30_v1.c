/* rva 77104 (0x12d30) 32 B FPO/esp gap chunk
 * mov eax,[esp+4]; xor edx,edx; mov ecx,[eax]; mov [ecx+0x6c],edx;
 * mov ecx,[eax]; mov [ecx+0x14],edx; ret  (cdecl, 1 param)
 * two reloads of [p]; zero staged in edx once */
void __cdecl w31b_12d30(long **p)
{
    long *t;
    long z;

    t = *p;
    z = 0;
    t[27] = z;
    t = *p;
    t[5] = z;
}