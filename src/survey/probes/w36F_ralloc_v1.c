/* w36F 0x6dd80 (64B, tail 8bff+8da42400000000) v1 — MMAllocPtr + read loop
 * FA: push ebx; mov edx,0x8000; push esi; xor ebx,ebx; push edi; mov esi,ecx;
 * call @MMAllocPtr@8; mov edi,eax; test esi,esi; jle ret;
 * L: mov eax,esi; lea ecx,[edi+ebx]; sub eax,ebx; push eax; push ecx;
 * push 0; call [MP_Read]; add esp,0xc; add ebx,eax; cmp ebx,esi; jl L;
 * ret: mov eax,edi; pop edi; pop esi; pop ebx; ret
 */
extern char * __fastcall MMAllocPtr(long a, long b);
extern long (*w36f_mpr)(long, char *, long);   /* -> ?MP_Read@@3P6AJJPAEJ@ZA */

char * __fastcall w36f_ralloc(long count)
{
    char *buf;
    long got;
    buf = MMAllocPtr(count, 0x8000);
    got = 0;
    if (count > 0) {
        do {
            got = got + w36f_mpr(0, buf + got, count - got);
        } while (got < count);
    }
    return buf;
}