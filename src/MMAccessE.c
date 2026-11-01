// _MMAccessE@12 @ rva 0x35dc0 (48 B) — FA asm: mov eax,[esp+4] / test / jne
//   / xor eax,eax / ret 0xc / mov ecx,[eax+8] / test / jne / xor eax,eax /
//   ret 0xc / mov eax,[esp+8] / add eax,ecx / ret 0xc.  _MMLockE@16 (wave
//   17) is an identity forwarder to this: return handle->data(=*(long*)
//   (h+8)) + offset, 0 on null handle or null data.  Plain C stdcall:
//   return-0-first at both guards; CL's ecx=p/eax=off plan needs probing
//   (CL may load off before p — FA's add eax,ecx pins off in eax).
long __stdcall MMAccessE(long h, long off, long c)
{
    long p;
    if (h == 0) return 0;
    p = *(long *)(h + 8);
    if (p == 0) return 0;
    return p + off;
}