// _Seek@12 @ rva 0xa9f50 (48 B) — stdcall seek wrapper returning a 0/-1 flag:
//   mov eax,[esp+0xc] (how) / mov ecx,[esp+8] (pos) / mov edx,[esp+4] (fd) /
//   push eax / push ecx / push edx / call SeekTell / lea ecx,[eax+1] /
//   cmp ecx,1 / sbb edx,edx (CF = (unsigned)(tell+1) < 1, i.e. tell == -1) /
//   mov ax,dx (66 8b c2, ax-only short return convention) / ret 0xc
// Wave-13 sbb-borrow pair: the {-1,0} ternary arms with the unsigned
// (t+1) < 1 compare; short return type gets FA's 16-bit copy instead of
// movsx. Plain C exact (probe b18c_Seek, round 1 — only the call rel32
// differs inside the reloc window).
extern long __stdcall SeekTell(int fd, long pos, int how);

short __stdcall Seek(int fd, long pos, int how)
{
    long t = SeekTell(fd, pos, how);
    return (unsigned)(t + 1) < 1 ? -1 : 0;
}
