/* StallSpeed — pilot 2 (chunk @ rva 0x9b1f0, size 0x30, FPO locals=1
 * cbParams=1 flags=07 00). Callee at chunk rva 0xb2f0 is UNNAMED in FA.SMS
 * (gap chunk 0xb0a0) — C placeholder name remapped by fitobj --map.
 *
 * FA asm:
 *   mov ecx,[esp+4]; sub esp,4; lea eax,[esp]; push 0; push 0; push eax;
 *   push ecx; call <$FA$_t_40b0a0>; mov eax,[esp]; cmp eax,1; jg L;
 *   mov eax,1; L: add esp,4; ret 4
 * FPO: offStart=0x9b1f0 cbProcSize=0x30 cdwLocals=1 cbParams=1 flags=07 00
 * (pad 8d 9b 00 ... to 0x30 from 0x2a)
 */
extern long __stdcall Callee(long spd, long *ploc, long a, long b);

long __stdcall StallSpeed(long spd)
{
    long local;
    long r;
    Callee(spd, &local, 0, 0);
    r = local;
    if (r <= 1)
        r = 1;
    return r;
}