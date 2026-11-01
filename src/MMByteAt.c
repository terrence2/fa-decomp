// _MMByteAt @ rva 0x35e00 (12 B) — mov eax,[esp+4] / mov ecx,[esp+8] /
//   mov al,[ecx+eax] / ret: *(char *)(p + o). Probe d1_mmba1 byte-exact.
char MMByteAt_q(char *p, int o)
{
    return *(char *)(p + o);
}
