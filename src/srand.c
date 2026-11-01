// _srand @ rva 0xd5c20 (12 B) — call __getptd / mov ecx,[esp+4] /
//   mov [eax+0x14],ecx / ret — seed the per-thread CRT data (+0x14).
extern void *_getptd(void);

void __cdecl srand_(unsigned s)
{
    *(unsigned *)((char *)_getptd() + 0x14) = s;
}