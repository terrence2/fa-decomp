// @Checksum@8 @ rva 0x119f0 (80 B) — FA asm: sub esp,8 / mov eax,edx / dec edx /
//   test eax / mov [esp+4],ecx (p spill) / push ebx / mov dword [esp+4],0
//   (sum init) / je / ror dword [esp+4],3 / mov eax,[esp+8] (q) / xor ecx /
//   mov ebx,[esp+4] (sum) / inc eax / mov [esp+8],eax / mov cl,[eax-1] /
//   add ebx,ecx / mov ecx,edx / dec edx / mov [esp+4],ebx / test / jne /
//   mov eax,[esp+4] / pop ebx / add esp,8 / ret / 05 00000000+8da424 pad.
extern unsigned long __cdecl _lrotr(unsigned long, int);

unsigned long __fastcall Checksum_q(const void *pv, unsigned long n)
{
    unsigned long sum = 0;
    const unsigned char *p = (const unsigned char *)pv;
    while (n-- != 0) {
        sum = _lrotr(sum, 3) + *p++;
    }
    return sum;
}
