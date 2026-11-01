// _MMWordAt @ rva 0x35e10 (13 B) — mov eax,[esp+4] / mov ecx,[esp+8] /
//   mov ax,[ecx+eax] / ret: *(short *)(p + o). Probe d5_mmwa1 byte-exact
//   (same bytes also serve _MMUWordAt).
short MMWordAt_q(char *p, int o)
{
    return *(short *)(p + o);
}
